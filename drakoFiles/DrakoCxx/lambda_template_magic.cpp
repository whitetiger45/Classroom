#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <cctype>

namespace pl
{
    namespace detail
    {
        template <typename Lambda>
        struct lambda_result_helper;

        template <typename Result, typename Class, typename... Arg>
        struct lambda_result_helper < Result(Class::*)(Arg...) const >
        {
            typedef Result type;
        };

        template <typename Lambda>
        struct lambda_result
        {
            typedef typename lambda_result_helper < decltype(&Lambda::operator()) >::type type;
        };

        template <typename Functor, typename Iterator>
        class grep_iterator
        {
        public:
            typedef typename Iterator::value_type source_type;
            typedef typename Iterator::difference_type difference_type;
            typedef source_type value_type;
            typedef value_type const & reference;
            typedef value_type const * pointer;
            typedef std::forward_iterator_tag iterator_category;

            grep_iterator(Functor f, Iterator it, Iterator end)
                : m_f(f)
                , m_it(it)
                , m_end(end)
            {
                while (m_it != m_end && !m_f(*m_it))
                    ++m_it;
            }

            grep_iterator(grep_iterator const & source)
                : m_f(source.m_f)
                , m_it(source.m_it)
                , m_end(source.m_end)
            {
            }

            grep_iterator & operator = (grep_iterator const & source)
            {
                m_f = source.m_f;
                m_it = source.m_it;
                m_end = source.m_end;
                return *this;
            }

            grep_iterator & operator ++ ()
            {
                if (m_it == m_end)
                    return *this;

                do
                {
                    ++m_it;
                } while (m_it != m_end && !m_f(*m_it));
                return *this;
            }

            grep_iterator operator ++ (int)
            {
                if (m_it == m_end)
                    return *this;

                grep_iterator old(*this);
                
                do
                {
                    ++m_it;
                } while (m_it != m_end && !m_f(*m_it));

                return old;
            }

            bool operator == (grep_iterator const & other) const
            {
                return m_it == other.m_it;
            }

            bool operator != (grep_iterator const & other) const
            {
                return m_it != other.m_it;
            }

            reference operator * () const
            {
                return *m_it;
            }

            pointer operator -> () const
            {
                return &(*m_it);
            }

        private:
            Functor m_f;
            Iterator m_it;
            Iterator m_end;
        };

        template <typename Functor, typename SContainer>
        class grep_proxy
        {
        public:
            typedef typename SContainer::const_iterator source_iterator;

            grep_proxy(Functor f, SContainer const & c)
                : m_f(f)
                , m_c(c)
            {
            }

            template <typename TContainer>
            operator TContainer () const
            {
                return to<TContainer>();
            }

            template <typename TContainer>
            TContainer to() const
            {
                TContainer c;
                std::copy_if(std::begin(m_c), std::end(m_c), std::inserter(c, std::end(c)), m_f);
                return c;
            }

            
            grep_iterator<Functor, source_iterator> begin() const
            {
                return grep_iterator<Functor, source_iterator>(m_f, std::begin(m_c), std::end(m_c));
            }

            grep_iterator<Functor, source_iterator> end() const
            {
                return grep_iterator<Functor, source_iterator>(m_f, std::end(m_c), std::end(m_c));
            }
            
        private:
            Functor m_f;
            SContainer const & m_c;
        };

        template <typename Functor, typename Iterator>
        class map_iterator
        {
        public:
            typedef typename Iterator::value_type source_type;
            typedef typename Iterator::difference_type difference_type;
            typedef typename lambda_result<Functor>::type value_type;
            typedef value_type const & reference;
            typedef value_type const * pointer;
            typedef std::forward_iterator_tag iterator_category;

            map_iterator(Functor f, Iterator it)
                : m_f(f)
                , m_it(it)
            {
            }

            map_iterator(map_iterator const & source)
                : m_f(source.m_f)
                , m_it(source.m_it)
            {
            }

            map_iterator & operator = (map_iterator const & source)
            {
                m_f = source.m_f;
                m_it = source.m_it;
                return *this;
            }

            map_iterator & operator ++ ()
            {
                ++m_it;
                return *this;
            }

            map_iterator operator ++ (int)
            {
                map_iterator old(*this);
                ++m_it;
                return old;
            }

            bool operator == (map_iterator const & other) const
            {
                return m_it == other.m_it;
            }

            bool operator != (map_iterator const & other) const
            {
                return m_it != other.m_it;
            }

            reference operator * () const
            {
                m_val = m_f(*m_it);
                return m_val;
            }

            pointer operator -> () const
            {
                m_val = m_f(*m_it);
                return &m_val;
            }

        private:
            Functor m_f;
            Iterator m_it;
            mutable value_type m_val;
        };

        template <typename Functor, typename SContainer>
        class map_proxy
        {
        public:
            typedef typename SContainer::const_iterator source_iterator;

            map_proxy(Functor f, SContainer const & c)
                : m_f(f)
                , m_c(c)
            {
            }

            template <typename TContainer>
            operator TContainer () const
            {
                return to<TContainer>();
            }

            template <typename TContainer>
            TContainer to() const
            {
                TContainer c;
                std::transform(std::begin(m_c), std::end(m_c), std::inserter(c, std::end(c)), m_f);
                return c;
            }

            map_iterator<Functor, source_iterator> begin() const
            {
                return map_iterator<Functor, source_iterator>(m_f, std::begin(m_c));
            }

            map_iterator<Functor, source_iterator> end() const
            {
                return map_iterator<Functor, source_iterator>(m_f, std::end(m_c));
            }

        private:
            Functor m_f;
            SContainer const & m_c;
        };
    }

    template <typename Functor, typename Container>
    detail::grep_proxy<Functor, Container> grep(Functor f, Container const & c)
    {
        return detail::grep_proxy<Functor, Container>(f, c);
    }

    template <typename Functor, typename Container>
    detail::map_proxy<Functor, Container> map(Functor f, Container const & c)
    {
        return detail::map_proxy<Functor, Container>(f, c);
    }
}


int main()
{
    using pl::map;
    using pl::grep;

    std::string hello = "Hello world!";
    std::string caps = map([](char c) { return std::toupper(c); }, hello).to<std::string>();

    std::cout << caps << std::endl;

    std::vector<double> numbers = { 0.3, 0.4, 0.5, 0.6, 0.7 };
    for (auto && n : map([](double d) { return static_cast<int>(d * 2.0 + 1) / 2; }, numbers))
        std::cout << n << std::endl;

    std::string lower = grep([](char c) { return std::islower(c); }, hello).to<std::string>();
    std::cout << lower << std::endl;

    for (auto && n : grep([](double d) { return d > 0.5; }, numbers))
        std::cout << n << std::endl;

    std::cin.get();

    return 0;
}
