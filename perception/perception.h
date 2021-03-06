// Copyright @2018 Pony AI Inc. All rights reserved.

#pragma once

#include<stdio.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "common/proto/perception.pb.h"
#include "common/utils/common/defines.h"
#include "common/utils/common/optional.h"
#include "homework2/pointcloud.h"
#include "common/utils/math/math_utils.h"
#include "homework4/camera_lidar_fusion_utils.h"

#include "common/utils/display/color.h"
#include "common/utils/file/path.h"
#include "common/utils/strings/format.h"

class Perception {
 public:
  Perception() = default;

  interface::perception::PerceptionObstacles RunPerception(const PointCloud& pointcloud,
                                                           const utils::Optional<cv::Mat>& pimage, const Eigen::VectorXd& intrinsic,
														   const Eigen::Affine3d& extrinsic, 
														   const char video_name[], int frameID);

  DISALLOW_COPY_MOVE_AND_ASSIGN(Perception);
};

