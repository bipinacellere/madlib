/* ----------------------------------------------------------------------- *//**
 *
 * @file PGCommon.hpp
 *
 * @brief Common header file for PostgreSQL port
 *
 * This file is included by all PostgreSQL-specific source files.
 *
 *//* ----------------------------------------------------------------------- */

#ifndef MADLIB_POSTGRES_COMMON_HPP
#define MADLIB_POSTGRES_COMMON_HPP

// Handle faist Boost assertions in a sophisticated way. The handler is
// implemented in the MADlib core library.
#define BOOST_ENABLE_ASSERT_HANDLER

#include <dbal/dbal.hpp>
#include <utils/memory.hpp>

extern "C" {
    #include <postgres.h>   // for Oid, Datum
}

namespace madlib {

namespace dbconnector {

using namespace dbal;
using namespace utils::memory;

typedef AnyType (MADFunction)(AbstractDBInterface &, AnyType);

// Forward declarations
// ====================

// Abstract Base Classes

class PGInterface;
class PGAllocator;

} // namespace dbconnector

} // namespace madlib

#endif
