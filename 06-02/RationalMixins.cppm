export module rational:mixins;

export namespace Math
{

template <typename T>
struct Addable
{
    friend T operator+(T lhs, const T& rhs)
    {
        return lhs += rhs;
    }
};

template <typename T>
struct Subtractable
{
    friend T operator-(T lhs, const T& rhs)
    {
        return lhs -= rhs;
    }
};

template <typename T>
struct Multipliable
{
    friend T operator*(T lhs, const T& rhs)
    {
        return lhs *= rhs;
    }
};

template <typename T>
struct Dividable
{
    friend T operator/(T lhs, const T& rhs)
    {
        return lhs /= rhs;
    }
};

template <typename T>
struct Incrementable
{
    T operator++(int)
    {
        auto& self = static_cast<T&>(*this);
        T temp(self);
        ++self;
        return temp;
    }
};

template <typename T>
struct Decrementable
{
    T operator--(int)
    {
        auto& self = static_cast<T&>(*this);
        T temp(self);
        --self;
        return temp;
    }
};

}