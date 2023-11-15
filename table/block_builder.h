// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
#define STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_

#include <cstdint>
#include <vector>

#include "leveldb/slice.h"

namespace leveldb {

struct Options;

class BlockBuilder {
 public:
  explicit BlockBuilder(const Options* options);

  BlockBuilder(const BlockBuilder&) = delete;
  BlockBuilder& operator=(const BlockBuilder&) = delete;

  // Reset the contents as if the BlockBuilder was just constructed.
  /**
   * @brief 重设内容，通常在Finish()之后调用
  */
  void Reset();

  // REQUIRES: Finish() has not been called since the last call to Reset().
  // REQUIRES: key is larger than any previously added key
  /**
   * @brief 添加一个key-value对 要求Reset()之后没有调用故Finsi()
   * @param[in] key key
   * @param[in] value value
  */
  void Add(const Slice& key, const Slice& value);

  // Finish building the block and return a slice that refers to the
  // block contents.  The returned slice will remain valid for the
  // lifetime of this builder or until Reset() is called.
  /**
   * @brief 返回Slice的生存周期：Builder的生存周期，或者Reset()被调用
  */
  Slice Finish();

  // Returns an estimate of the current (uncompressed) size of the block
  // we are building.
  size_t CurrentSizeEstimate() const;  ///< 返回正在构建的block的未压缩大小-估计值

  // Return true iff no entries have been added since the last Reset()
  /**
   * @brief  没有entry就返回true
  */
  bool empty() const { return buffer_.empty(); }

 private:
  const Options* options_;
  std::string buffer_;              // block的内容
  std::vector<uint32_t> restarts_;  // 重启点
  int counter_;                     // 重启后生成的entry数
  bool finished_;                   // Has Finish() been called?
  std::string last_key_;            // 记录最后添加的key
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
