// -*- mode: C++ -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014, JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/o2r other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
#ifndef JSK_PCL_ROS_GRID_MAP_H_
#define JSK_PCL_ROS_GRID_MAP_H_

#include "jsk_pcl_ros/grid_index.h"
#include "jsk_pcl_ros/grid_line.h"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <map>
#include <set>
#include <Eigen/Geometry>

namespace jsk_pcl_ros
{

   // infinity range, might be slow...
  class GridMap
  {
  public:
    typedef boost::shared_ptr<GridMap> Ptr;
    GridMap(double resolution, const std::vector<float>& coefficients);
    virtual ~GridMap();
    virtual void registerPoint(const pcl::PointXYZRGB& point);
    virtual void registerLine(const pcl::PointXYZRGB& from, const pcl::PointXYZRGB& to);
    virtual void registerPointCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud);
    virtual void registerIndex(const GridIndex::Ptr& index);
    virtual void registerIndex(const int x, const int y);
    virtual void pointToIndex(const pcl::PointXYZRGB& point, GridIndex::Ptr index);
    virtual void pointToIndex(const Eigen::Vector3f& point, GridIndex::Ptr index);
    virtual void indicesToPointCloud(const std::vector<GridIndex::Ptr>& indices,
                                     pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud);
    virtual bool getValue(const GridIndex::Ptr& index);
    virtual bool getValue(const GridIndex& index);
    virtual bool getValue(const int x, const int y);
    virtual void gridToPoint(GridIndex::Ptr index, Eigen::Vector3f& pos);
    virtual void gridToPoint(const GridIndex& index, Eigen::Vector3f& pos);
    virtual void gridToPoint2(const GridIndex& index, Eigen::Vector3f& pos);
    virtual void fillRegion(const Eigen::Vector3f& start, std::vector<GridIndex::Ptr>& output);
    virtual void fillRegion(const GridIndex::Ptr start, std::vector<GridIndex::Ptr>& output);
  protected:    
    typedef std::map<int, std::set<int> > Row;
    typedef Row::iterator RowIterator;
    typedef std::set<int> Column;
    typedef Column::iterator ColumnIterator;
    double resolution_;
    Eigen::Vector3f O;
    
    // plane parameter
    Eigen::Vector3f normal_;
    double d_;
    
    Eigen::Vector3f ex_, ey_;
    
    std::vector<GridLine::Ptr> lines_;
    std::map<int, std::set<int> > data_;
  private:
  };
  
}

#endif
