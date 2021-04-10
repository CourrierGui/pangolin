#pragma once

#include <pgl-math/impl/matrix.hpp>
#include <limits>
#include <cmath>

namespace pgl {

  template<container cont>
    inline constexpr auto max(const cont& vec) noexcept
    -> typename cont::value_type
    {
      auto max = std::numeric_limits<typename cont::value_type>::min();
      for (auto elem: vec) {
        if (elem > max)
          max = elem;
      }
      return max;
    }

  template<container cont>
    inline constexpr auto min(const cont& vec) noexcept
    -> typename cont::value_type
    {
      auto min = std::numeric_limits<typename cont::value_type>::max();
      for (auto elem: vec) {
        if (elem < min)
          min = elem;
      }
      return min;
    }

  template<container cont>
    inline constexpr auto max(const cont& vec, const cont& max) noexcept
    -> cont
    {
      cont res{vec};
      auto res_it = res.begin();
      auto max_it = max.begin();
      while (res_it != res.end() || max_it != max.end()) {
        if (*res_it > *max_it) {
          *res_it = *max_it;
        }
        ++res_it;
        ++max_it;
      }
      return res;
    }

  template<container cont>
    inline constexpr auto min(const cont& vec, const cont& min) noexcept
    -> cont
    {
      cont res{vec};
      auto res_it = res.begin();
      auto min_it = min.begin();
      while (res_it != res.end() || min_it != min.end()) {
        if (*res_it < *min_it) {
          *res_it = *min_it;
        }
        ++res_it;
        ++min_it;
      }
      return res;
    }

  template<container cont>
    inline constexpr auto operator<(
      const cont& lhs,
      const cont& rhs) noexcept
    -> typename cont::template container_of<bool>
    {
      typename cont::template container_of<bool> res;
      auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
      for (auto& elem: res) {
        elem = (*(lhs_it++) < *(rhs_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto operator>(
      const cont& lhs,
      const cont& rhs) noexcept
    -> typename cont::template container_of<bool>
    {
      typename cont::template container_of<bool> res;
      auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
      for (auto& elem: res) {
        elem = (*(lhs_it++) > *(rhs_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto operator<=(
      const cont& lhs,
      const cont& rhs) noexcept
    -> typename cont::template container_of<bool>
    {
      typename cont::template container_of<bool> res;
      auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
      for (auto& elem: res) {
        elem = (*(lhs_it++) <= *(rhs_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto operator>=(
      const cont& lhs,
      const cont& rhs) noexcept
    -> typename cont::template container_of<bool>
    {
      typename cont::template container_of<bool> res;
      auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
      for (auto& elem: res) {
        elem = (*(lhs_it++) >= *(rhs_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto operator==(
      const cont& lhs,
      const cont& rhs) noexcept
    -> typename cont::template container_of<bool>
    {
      typename cont::template container_of<bool> res;
      auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
      for (auto& elem: res) {
        elem = (*(lhs_it++) == *(rhs_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto operator!=(
      const cont& lhs,
      const cont& rhs) noexcept
    -> typename cont::template container_of<bool>
    {
      typename cont::template container_of<bool> res;
      auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
      for (auto& elem: res) {
        elem = (*(lhs_it++) != *(rhs_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto min_element(cont& vect) noexcept
    -> typename cont::value_type&
    {
      auto min_elem = vect.begin();
      auto min      = *min_elem;
      for (auto it=vect.begin(); it!=vect.end(); ++it) {
        if (*it < min) {
          min = *it;
          min_elem = it;
        }
      }
      return *min_elem;
    }

  template<container cont>
    inline constexpr auto max_element(cont& vect) noexcept
    -> typename cont::value_type&
    {
      auto max_elem = vect.begin();
      auto max = *max_elem;
      for (auto it=vect.begin(); it!=vect.end(); ++it) {
        if (*it > max) {
          max = *it;
          max_elem = it;
        }
      }
      return *max_elem;
    }

  template<container cont>
    inline constexpr auto min(
      const cont& vect,
      typename cont::value_type min_val) noexcept
    -> cont
    {
      cont res{vect};
      for (auto& e: res) { if (e < min_val) { e = min_val; } }
      return res;
    }

  template<container cont>
    inline constexpr auto max(
      const cont& vect,
      typename cont::value_type max_val) noexcept
    -> cont
    {
      cont res{vect};
      for (auto& e: res) { if (e > max_val) { e = max_val; } }
      return res;
    }

  template<container cont>
    inline constexpr auto clamp(
      const cont& x, typename cont::value_type lb,
      typename cont::value_type ub) noexcept
    -> cont
    {
      return min(max(x, lb), ub);
    }

  template<container cont>
    inline constexpr auto clamp(const cont& x, const cont& lb, const cont& ub) noexcept
    -> cont
    {
      return min(max(x, lb), ub);
    }

  template<container cont>
    inline constexpr auto saturate(const cont& vect) -> cont {
      return clamp(vect, typename cont::value_type{0}, typename cont::value_type{1});
    }

  template<container cont>
    inline constexpr auto any(const cont& vect) noexcept -> bool {
      bool res = false;
      for (auto e: vect) { res |= e; }
      return res;
    }

  template<container cont>
    inline constexpr auto all(const cont& vect) noexcept -> bool {
      bool res = true;
      for (const auto& e: vect) { res &= e; }
      return res;
    }

  template<container cont, typename Function>
    inline constexpr auto select(
      const cont& vect, Function& condition,
      typename cont::value_type on_true, typename cont::value_type on_false) noexcept
    -> cont
    {
      cont res{vect};
      for (auto& e: res) { condition(e) ? on_true : on_false; }
      return res;
    }

  template<container cont, number type>
    inline constexpr auto apply(
      type (*func)(type),
      const cont& vect)
    -> cont
    {
      cont res;
      auto it=vect.begin();
      for (auto& e: res) {
        e = func(*(it++));
      }
      return res;
    }

  template<container cont, number type>
    inline constexpr auto apply(
      type (*func)(type,type),
      const cont& x,
      const cont& y)
    -> cont
    {
      cont res;
      auto x_it=x.begin();
      auto y_it=y.begin();
      for (auto& e: res) {
        e = func(*(x_it++), *(y_it++));
      }
      return res;
    }

  template<container cont>
    inline constexpr auto exp(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::exp, vect);
    }

  template<container cont>
    inline constexpr auto log2(const cont& vect) noexcept -> cont {
      return apply<cont, typename cont::value_type>(std::log2, vect);
    }

  template<container cont>
    inline constexpr auto log10(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::log10, vect);
    }

  template<container cont>
    inline constexpr auto log(const cont& vect) noexcept -> cont {
      return apply<cont, typename cont::value_type>(std::log, vect);
    }

  template<container cont>
    inline constexpr auto tan(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::tan, vect);
    }

  template<container cont>
    inline constexpr auto atan(const cont& vect) noexcept -> cont {
      return apply<cont, typename cont::value_type>(std::atan, vect);
    }

  template<container cont>
    inline constexpr auto atan(const cont& x, const cont& y) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::atan2, x, y);
    }

  template<container cont>
    inline constexpr auto cos(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::cos, vect);
    }

  template<container cont>
    inline constexpr auto acos(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::acos, vect);
    }

  template<container cont>
    inline constexpr auto sin(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::sin, vect);
    }

  template<container cont>
    inline constexpr auto asin(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::asin, vect);
    }

  template<container cont>
    inline constexpr auto cosh(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::cosh, vect);
    }

  template<container cont>
    inline constexpr auto acosh(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::acosh, vect);
    }

  template<container cont>
    inline constexpr auto sinh(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::sinh, vect);
    }

  template<container cont>
    inline constexpr auto asinh(const cont& vect) noexcept -> cont {
      return apply<cont,typename cont::value_type>(std::asinh, vect);
    }

  /**
   * Create a view matrix which transforms the coordinates so that the user
   * looks at the target vector.
   *
   * @param camera Position of the camera
   * @param target Position of the target to look at
   * @param up Vector pointing in the up direction
   *
   * @return View matrix
   */
  template<number type>
    inline constexpr auto look_at(
      const vector<type,3>& camera,
      const vector<type,3>& target,
      const vector<type,3>& up) noexcept
    -> matrix<type,4>
    {
      auto f{normalize(target - camera)};
      auto s{normalize(cross(f, up))};
      auto u{cross(s, f)};

      return matrix<type,4>{
        s.x, u.x, -f.x, type{0},
        s.y, u.y, -f.y, type{0},
        s.z, u.z, -f.z, type{0},
        -dot(s, camera), -dot(u, camera), dot(f, camera), type{1},
      };
    }

  template<number type>
    inline constexpr auto ortho(
      type left, type right,
      type bottom, type top) noexcept
    -> matrix<type, 4>
    {
      return pgl::matrix<type,4>{
        type{2} / (right - left), type{0}, type{0}, type{0},
        type{0}, type{2} / (top - bottom), type{0}, type{0},
        type{0}, type{0}, type{1}, type{0},
        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom), type{0}, type{1}
      };
    }

  template<number type>
    inline constexpr auto ortho(
      type left, type right,
      type bottom, type top,
      type zNear, type zFar) noexcept
    -> matrix<type,4>
    {
      return {
        type{2}/(right-left), type{0}, type{0}, type{0},
        type{0}, type{2}/(top-bottom), type{0}, type{0},
        type{0}, type{0}, type{2}/(zFar-zNear), type{0},
        -(right+left)/(right-left),
        -(top+bottom)/(top-bottom),
        -(zNear+zFar)/(zFar-zNear),
        type{1}
      };
    }

  template<number type>
    inline constexpr auto translate(
      const matrix<type,4>& mat,
      const vector<type,3>& trans)
    -> matrix<type,4>
    {
      auto res{mat};
      res.row(3,
              mat.row(0)*trans.x
            + mat.row(1)*trans.y
            + mat.row(2)*trans.z
            + mat.row(3));
      return res;
    }

  template<number type>
    inline constexpr auto rotate(
      const matrix<type,4>& mat,
      const type& radians,
      vector<type,3> axis)
    -> matrix<type,4>
    {
      axis = normalize(axis);
      auto theta = radians;
      auto c = std::cos(theta);
      auto s = std::sin(theta);
      auto temp{(type{1} - c) * axis};

      matrix<type,3> rotation{
        axis.x * temp.x + c, axis.y * temp.x + axis.z * s, axis.z * temp.x - axis.y * s,
        axis.x * temp.y - axis.z * s, axis.y * temp.y + c, axis.z * temp.y + axis.x * s,
        axis.x * temp.z + axis.y * s, axis.y * temp.z - axis.x * s, axis.z * temp.z + c
      };

      return matrix_from_row_vectors(
        mat.row(0) * rotation.at(0, 0)
      + mat.row(1) * rotation.at(0, 1)
      + mat.row(2) * rotation.at(0, 2),
        mat.row(0) * rotation.at(1, 0)
      + mat.row(1) * rotation.at(1, 1)
      + mat.row(2) * rotation.at(1, 2),
        mat.row(0) * rotation.at(2, 0)
      + mat.row(1) * rotation.at(2, 1)
      + mat.row(2) * rotation.at(2, 2),
        mat.row(3));
    }

  template<number type>
    inline constexpr auto scale(const matrix<type,4>& mat, const vector<type,3>& scale)
    -> matrix<type,4>
    {
      return matrix_from_row_vectors(
        mat.row(0) * scale.x,
        mat.row(1) * scale.y,
        mat.row(2) * scale.z,
        mat.row(3)
        );
    }

} /* end of namespace pgl */
