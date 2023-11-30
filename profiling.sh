#!/bin/bash

create_files() {
  local size=$1
  local count=$2
  local directory=$3

  for ((i = 1; i <= count; i++)); do
    dd if=/dev/zero of="$directory/file$i" bs=$size count=1 status=none
  done
}

create_recursive_files() {
  local size=$1
  local count=$2
  local directory=$3

  if [ $count -eq 0 ]; then
    return
  fi

  mkdir -p "$directory"
  create_files $size $count "$directory"

  for ((i = 1; i <= count; i++)); do
    create_recursive_files $size $count "$directory/subdir$i"
  done
}


# Task 1: 100 files of 1GB each
echo "Creating 100 files of 1GB each..."
time create_files 1G 100 "dir1"

# Task 2: 10000 files of 10MB each
echo "Creating 10000 files of 10MB each..."
time create_files 10M 10000 "dir2"

# Task 3: 10000 files recursively with a sub-directory structure
echo "Creating 10000 files recursively with sub-directory structure..."
time create_recursive_files 10M 100 "dir3"

echo "All tasks completed!"
