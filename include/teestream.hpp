#pragma once
#include <vector>
#include <ostream>

namespace qlog {

class TeeStream: public std::ostream
{
public:
    typedef std::ostream& (*Manip)(std::ostream &);

    template <typename ...Ts>
    TeeStream(Ts & ... s)
        : std::ostream(nullptr)
        , _mutex()
        , _prefix()
        , _downstream{(&s)...}
    { }

    virtual ~TeeStream() { }

    // add new stream
    void push(std::ostream& s) {
        _downstream.push_back(&s);
    }

    void pop() {
        _downstream.pop_back();
    }

    template <typename T>
    TeeStream & operator<<(T && obj) {
        std::lock_guard<std::mutex> lock(_mutex);
        for (std::ostream* s: _downstream) {
            (*s) << std::forward<T>(obj);
        }
        return *this;
    }

    // Special case for manipulators (since they require de-overloading)
    TeeStream & operator<<(std::ostream & (*manip)(std::ostream &)) {
        std::lock_guard<std::mutex> lock(_mutex);
        for (std::ostream* s: _downstream) {
            manip(*s);
        }
        return *this;
    }

    void _print() { }
    
    template <typename T, typename ... Ts>
    void _print(T && obj, Ts && ... rest) {
        (*this) << std::forward<T>(obj);
        _print(std::forward<Ts>(rest)...);
    }

    template <typename T>
    void _printcomma(T && obj) {
        (*this) << std::forward<T>(obj);
    }
    
    template <typename T, typename ... Ts>
    void _printcomma(T && obj, Ts && ... rest) {
        (*this) << std::forward<T>(obj) << ", ";
        _print(std::forward<Ts>(rest)...);
    }

    template <typename ... T>
    TeeStream & print(T && ... args) {
        _print(_prefix, std::forward<T>(args)...);
        return *this;
    }

    void set_prefix(const char* prefix) { _prefix = prefix; }

    size_t size() const { return _downstream.size(); }

private:
    std::mutex _mutex;
    std::string _prefix;
    std::vector<std::ostream*> _downstream;
};

} // namespace qlog
