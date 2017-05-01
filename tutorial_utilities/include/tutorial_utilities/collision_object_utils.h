/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2016, Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 *  collision_object_utils.h
 *
 *  Created on: Feb 28, 2016
 *  Author: Bart and Jeroen
 */

#ifndef DESCARTES_COLLISION_OBJECT_UTILS_H
#define DESCARTES_COLLISION_OBJECT_UTILS_H

#include <ros/ros.h>

namespace tutorial_utilities
{
    /**
    * Function to test library compilation
    */
    void testCollisionUtils();

    //moveit_msgs::CollisionObject makeCollisionObject(std::string filepath, Eigen::Vector3d scale, std::string ID, Eigen::Affine3d pose);
}

#endif