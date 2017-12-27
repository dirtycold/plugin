#pragma once

//          Copyright Jeremy Coulon 2012-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/** @file */

#pragma once

#include "StringHandling.h"

//===========
//==  STD  ==
//===========
#include <istream>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

/// Data structure to store a version number
class Version
{
public:
    /// Default constructor
    /**
      * Version is initialized to v0.0.0.0
      */
    constexpr Version()
    {
        // Empty
    }

    /// Constructor taking 4 numbers as parameters
    /**
      * @param major    1st version number
      * @param minor    2nd version number
      * @param patch    3rd version number
      * @param tweak    4th version number
      */
    constexpr Version(unsigned short major,
                      unsigned short minor,
                      unsigned short patch,
                      unsigned short tweak)
        : major_(major),
          minor_(minor),
          patch_(patch),
          tweak_(tweak)
    {
        // Empty
    }

    /// Constructor from a string
    /**
      * @param version a string representing a version number. This string must be well formed.
      * @throw VersionException
      * @see Version::set(const std::string&)
      */
    explicit Version(const std::string& version)
    {
        set(version);
    }

    /// Get 1st version number
    constexpr unsigned short getMajor() const
    {
        return major_;
    }

    /// Get 2nd version number
    constexpr unsigned short getMinor() const
    {
        return minor_;
    }

    /// Get 3rd version number
    constexpr unsigned short getPatch() const
    {
        return patch_;
    }

    /// Get 4th version number
    constexpr unsigned short getTweak() const
    {
        return tweak_;
    }

    /// Set 1st version number
    constexpr void setMajor(unsigned short major)
    {
        major_ = major;
    }

    /// Set 2nd version number
    constexpr void setMinor(unsigned short minor)
    {
        minor_ = minor;
    }

    /// Set 3rd version number
    constexpr void setPatch(unsigned short patch)
    {
        patch_ = patch;
    }

    /// Set 4th version number
    constexpr void setTweak(unsigned short tweak)
    {
        tweak_ = tweak;
    }

    /// Set complete version number from 4 numbers
    constexpr void set(unsigned short major,
                       unsigned short minor,
                       unsigned short patch,
                       unsigned short tweak)
    {
        major_ = major;
        minor_ = minor;
        patch_ = patch;
        tweak_ = tweak;
    }

    /// Set complete version number from a string
    /**
      * The given string must be well formed.
      * It must be composed of 1 to 4 unsigned numbers separated by a dot '.' or comma ','.
      * If the string is bad formed, an exception is thrown.
      * This method provides the strong exception-safety guarantee.
      * @param version a string containing the version number
      * @throw VersionException
      */
    void set(const std::string& version)
    {
        unsigned short major, minor, patch, tweak;

        std::vector<std::string> splitResult;
        splitResult = split(version, '.');

        // Check that we have between 1 and 4 numbers in the version string
        if (splitResult.size() == 0 || splitResult.size() > 4)
            return;

        major = std::stoul(splitResult[0]);

        if (splitResult.size() >= 2)
            minor = std::stoul(splitResult[1]);
        else
            minor = 0;

        if (splitResult.size() >= 3)
            patch = std::stoul(splitResult[2]);
        else
            patch = 0;

        if (splitResult.size() == 4)
            tweak = std::stoul(splitResult[3]);
        else
            tweak = 0;

        major_ = major;
        minor_ = minor;
        patch_ = patch;
        tweak_ = tweak;
    }

    constexpr bool valid () const
    {
        if (major_ < 0 && minor_ < 0 || patch_ < 0 || tweak_ < 0)
            return false;
        else
            return true;
    }

private:
    unsigned short major_ = -1;
    unsigned short minor_ = -1;
    unsigned short patch_ = -1;
    unsigned short tweak_ = -1;
};

/// Equal operator of 2 version numbers
/**
  * @param v1   First version number
  * @param v2   Second version number
  * @return
  *         - True if the 2 versions are equal.
  *         - False otherwise.
  *
  * @note In order to use other comparison operators, see http://en.cppreference.com/w/cpp/utility/rel_ops/operator_cmp
  */
inline bool operator== (const Version& v1, const Version& v2)
{
    return std::forward_as_tuple(v1.getMajor(), v1.getMinor(), v1.getPatch(), v1.getTweak()) == std::forward_as_tuple(v2.getMajor(), v2.getMinor(), v2.getPatch(), v2.getTweak());
}

/// Less-than operator of 2 version numbers
/**
  * @param v1   First version number
  * @param v2   Second version number
  * @return
  *         - True if the first version number is less than the second version number.
  *         - False otherwise.
  *
  * @note In order to use other comparison operators, see http://en.cppreference.com/w/cpp/utility/rel_ops/operator_cmp
  */
inline bool operator< (const Version& v1, const Version& v2)
{
    return std::forward_as_tuple(v1.getMajor(), v1.getMinor(), v1.getPatch(), v1.getTweak()) < std::forward_as_tuple(v2.getMajor(), v2.getMinor(), v2.getPatch(), v2.getTweak());
}

/// Output stream operator
/**
  * @param os Output stream
  * @param v  Version number
  */
inline std::ostream& operator<<(std::ostream& os, const Version& v)
{
    os << v.getMajor()
       << '.' << v.getMinor()
       << '.' << v.getPatch()
       << '.' << v.getTweak();
    return os;
}

/// Input stream operator
/**
  * @param is Input stream
  * @param v Version number
  */
inline std::istream& operator>>(std::istream& is, Version& v)
{
    char separator;
    unsigned short major, minor, patch, tweak;
    is >> major >> separator >> minor >> separator >> patch >> separator >> tweak;
    v.set(major, minor, patch, tweak);
    return is;
}

