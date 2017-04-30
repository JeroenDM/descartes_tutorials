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
 *  path_generation.h
 *
 *  Created on: Feb 28, 2016
 *  Author: Bart and Jeroen
 */

#include <vector>
#include </usr/include/eigen3/Eigen/Geometry>


namespace tutorial_utilities
{
    std::vector<Eigen::Affine3d> line(	Eigen::Affine3d start_pose, Eigen::Affine3d end_pose, int steps)
	{
		Eigen::Vector3d translation_vector;
		translation_vector = end_pose.translation() - start_pose.translation();
		translation_vector = translation_vector / steps;
		Eigen::Translation<double,3> translate(translation_vector);

		std::vector<Eigen::Affine3d> poses;
		poses.push_back(start_pose);
		for(int i = 0; i < (steps - 1); ++i)
		{
			poses.push_back(translate * poses.back());
		}
		return poses;
	}
}