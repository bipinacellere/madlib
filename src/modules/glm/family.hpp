/* ----------------------------------------------------------------------- *//**
 *
 * @file family.hpp
 *
 *//* ----------------------------------------------------------------------- */

#ifndef MADLIB_MODULES_GLM_FAMILY_HPP
#define MADLIB_MODULES_GLM_FAMILY_HPP

#include <cmath>
#include <limits>

namespace madlib {

namespace modules {

namespace glm {

class Gaussian {
public:
    static double variance(const double &) { return 1.; }
    static double loglik(const double &y, const double &mu,
            const double &psi) {

        double theta = mu;
        double a = psi;
        double b = theta * theta / 2;
        double c = - y * y / (a * 2);
        c -= std::log(std::sqrt(2 * M_PI * a));

        return (y * theta - b) / a + c;
    }
    static std::string get_y_range() { return "y can be between negative infinity and positive infinity"; }
    static bool in_range(double y) { return true; }
};

class Poisson {
public:
    static double variance(const double &mu) { return mu; }
    static double loglik(const double &y, const double &mu,
            const double & /* psi */) {
        if (mu == 0) return - std::numeric_limits<double>::infinity();
        double theta = std::log(mu);
        double a = 1;
        double b = mu;
        double c = 0.;
        unsigned i = 0;
        for (i = 2; i <= y; i ++) { c -= std::log(i); }

        return (y * theta - b) / a + c;
    }
    static std::string get_y_range() { return "y should be an integer between 0 and positive infinity"; }
    static bool in_range(double y) { 
        double intpart;
        return (modf(y, &intpart)==0.0 && (y >= 0.0 
                                        && y <= std::numeric_limits<double>::max()));
    }
};

class Gamma {
public:
    static double variance(const double &mu) { return mu*mu; }
    static double loglik(const double &y, const double &mu,
            const double &psi) {
        double theta = -1./mu;
        double a = psi;
        double b = -std::log(-theta);
        double c = 1./psi*std::log(y/psi)-std::log(y)-lgamma(1./psi);

	return (y * theta - b) / a + c;
    }
    static std::string get_y_range() { return "y should be between 0 and positive infinity"; }
    static bool in_range(double y) { return (y >= 0.0 
                                          && y <= std::numeric_limits<double>::max()); }
};

class Inverse_gaussian {
public:
    static double variance(const double &mu) { return mu*mu*mu; }
    static double loglik(const double &y, const double &mu,
            const double &psi) {
        double theta = 1./2/mu/mu;
        double a = -psi;
        double b = 1./mu;
        double c = -1./(2*y*psi) - 1./2*std::log(2.*M_PI*y*y*y*psi);

	return (y * theta - b) / a + c;
    }
    static std::string get_y_range() { return "y should be between 0 and positive infinity"; }
    static bool in_range(double y) { return (y >= 0.0 
                                          && y <= std::numeric_limits<double>::max()); }
};

class Binomial {
public:
    static double variance(const double &mu) { return mu * (1 - mu); }
    static double loglik(const double &y, const double &mu,
            const double &psi) {
        if (mu == 0 || mu == 1) return 0;
        double theta = log(mu / (1 - mu));
        double a = 1;
        double b = 0;
        double c = log(1 - mu);
        return (y * theta - b) / a + c;
    }
    static std::string get_y_range() { return "y should be a boolean value or a boolean expression"; }
    static bool in_range(double y) { 
        double intpart;
        return (modf(y, &intpart)==0.0 && (y == 0.0 || y == 1.0));
    }
};

} // namespace glm

} // namespace modules

} // namespace madlib

#endif // defined(MADLIB_MODULES_GLM_FAMILY_HPP)