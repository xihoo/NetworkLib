// excerpts from http://code.google.com/p/xihoo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#ifndef xihoo_BASE_COPYABLE_H
#define xihoo_BASE_COPYABLE_H

namespace xihoo
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
};

};

#endif  // xihoo_BASE_COPYABLE_H

