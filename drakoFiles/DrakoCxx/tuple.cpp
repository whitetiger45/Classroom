#include <iostream>
#include <tuple>
#include <string>

namespace detail
{
    template <std::size_t... Ts>
    struct index {};

    template <std::size_t N, std::size_t... Ts>
    struct gen_seq : gen_seq<N - 1, N - 1, Ts...> {};

    template <std::size_t... Ts>
    struct gen_seq<0, Ts...> : index<Ts...> {};

    template <typename... Types>
    class proxy
    {
    public:
        proxy(Types... args)
            : args_(std::make_tuple(args...))
        {
        }

        template <typename ObjectType>
        operator ObjectType * () const
        {
            return create_object<ObjectType>(gen_seq<sizeof...(Types)>());
        }

    private:
        std::tuple<Types...> args_;

        template <typename ObjectType, std::size_t... indizes>
        ObjectType * create_object(index<indizes...>) const
        {
            return new ObjectType(std::get<indizes>(args_)...);
        }
    };
}

template <typename... Types>
detail::proxy<Types...> create(Types... args)
{
    return detail::proxy<Types...>(args...);
}

class foo
{
public:
    foo(std::string const & text = "")
        : text_(text)
    {
    }

    void print()
    {
        std::cout << text_ << std::endl;
    }

private:
    std::string text_;
};

int main()
{
    foo * f = create("hello world!");
    f->print();
    delete f;
    return 0;
}
