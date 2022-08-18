#pragma once

#include <pgl-math/utils.hpp>

namespace pgl {

    template<integral type, length dim,
             template<typename T, length d> class vector_type>
    struct base {
        template<typename T> using container_of = vector_type<T,dim>;

        inline constexpr explicit base(const type& e) noexcept;
        inline constexpr base() noexcept;
        inline constexpr base(const type arr[dim]) noexcept;
        inline constexpr base(std::convertible_to<type> auto ... args) noexcept;

        type elements[dim];
    };

    template<integral type,
             template<typename T, length d> class vector_type>
    struct base<type,4, vector_type> {
        template<typename T> using container_of = vector_type<T,4>;

        inline constexpr explicit base(const type& e) noexcept;
        inline constexpr base() noexcept;
        inline constexpr base(const type arr[4]) noexcept;
        inline constexpr base(std::convertible_to<type> auto ... args) noexcept;

        union {
            type elements[4];
            struct { vector_type<type,3> xyz; };
            struct { vector_type<type,2> xy, zw; };
            struct { type x, y, z, w; };
        };
    };

    template<integral type,
             template<typename T, length d> class vector_type>
    struct base<type,3, vector_type> {
        template<typename T> using container_of = vector_type<T,3>;

        inline constexpr explicit base(const type& e) noexcept;
        inline constexpr base() noexcept;
        inline constexpr base(const type arr[3]) noexcept;
        inline constexpr base(std::convertible_to<type> auto ... args) noexcept;

        union {
            type elements[3];
            struct { vector_type<type,2> xy; };
            struct { type x, y, z; };
        };
    };

    template<integral type,
             template<typename T, length d> class vector_type>
    struct base<type,2,vector_type> {
        template<typename T> using container_of = vector_type<T,2>;

        inline constexpr explicit base(const type& e) noexcept;
        inline constexpr base() noexcept;
        inline constexpr base(const type arr[2]) noexcept;
        inline constexpr base(std::convertible_to<type> auto ... args) noexcept;

        union {
            type elements[2];
            struct { type x, y; };
        };
    };

    template<integral type, length dim,
             template<typename T,length d> class vector_type>
    struct base_vector : public base<type,dim,vector_type> {
        using value_type     = type;
        using size_type      = int;
        using iterator       = type*;
        using const_iterator = const type*;

        struct raw_data {
            type data[dim];
            int size;

            inline constexpr raw_data(const type arr[dim]) noexcept :
                data{}, size{dim}
            {
                auto it = data, val = arr;

                while (it != data + dim)
                    *(it++) = *(val++);
            }
        };

        inline constexpr auto data() noexcept -> raw_data;
        inline constexpr auto size() const noexcept -> length;

        inline constexpr auto begin()        noexcept -> type*;
        inline constexpr auto begin()  const noexcept -> const type*;
        inline constexpr auto cbegin() const noexcept -> const type*;
        inline constexpr auto end()          noexcept -> type*;
        inline constexpr auto end()    const noexcept -> const type*;
        inline constexpr auto cend()   const noexcept -> const type*;

        inline constexpr explicit base_vector(const type& e) noexcept;
        inline constexpr base_vector() noexcept;
        inline constexpr base_vector(const type arr[dim]) noexcept;
        inline constexpr base_vector(std::convertible_to<type> auto ... args) noexcept;
    };

} /* end of namespace pgl */
