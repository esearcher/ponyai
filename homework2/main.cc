// Copyright @2018 Pony AI Inc. All rights reserved.

#include <iostream>

#include <glog/logging.h>

#include "homework2/pointcloud.h"

int main() {
  // Use absolute path for reading the data file.
  const PointCloud pointcloud = ReadPointCloudFromTxtFile(
      "/PublicCourse/homework2/sample_data/VelodyneDevice32c/0.txt");
  std::cout << "Total points read: " << pointcloud.points.size() << std::endl;
  std::cout << "Rotation: " << std::endl;
  std::cout << pointcloud.rotation << std::endl;
  std::cout << "Translation: " << std::endl;
  std::cout << pointcloud.translation.transpose() << std::endl;
  return 0;
}