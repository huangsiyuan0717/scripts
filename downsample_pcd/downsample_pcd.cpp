#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/filters/voxel_grid.h>
#include<pcl/point_cloud.h>
#include<pcl/pcl_config.h>

int main(int argc, char** argv)
{
    //pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    //pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) != 0)
    {
        return -1;
    }

    // pcl::PCDReader reader;
    // reader.read("../scans.pcd", *cloud);
    
    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
        << " data points (" << pcl::getFieldsList(*cloud) << ")." << std::endl;

    pcl::VoxelGrid<pcl::PointXYZ> filter;
    filter.setInputCloud(cloud);
    filter.setLeafSize(0.3f, 0.25f, 0.2f);
    filter.filter(*cloud_filtered);
    
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
        << " data points (" << pcl::getFieldsList(*cloud_filtered) << ")." << std::endl;
    
    pcl::io::savePCDFileASCII("../downsample1.pcd", *cloud_filtered);

    // pcl::PCLPointCloud2::Ptr cloud_tmp(new pcl::PCLPointCloud2());
    // // cloud_tmp = cloud_filtered;

    // pcl::PCDWriter writer;
    //  writer.write("../downsampled.pcd", *cloud_tmp,
    //     Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), false);


    return 0;
}