#include <gtest/gtest.h>
#include <pangolin/resource-manager.hpp>
#include <pangolin/profile.hpp>

TEST(TestResources, Root) {
  {
    std::string path = "/home/guillaume/dev/projects/pangolin";
    pgl::resources::set_root(path);
    const std::string& root = pgl::resources::root();

    ASSERT_EQ(root, "/home/guillaume/dev/projects/pangolin");
  }

  {
    std::string path = "/home/guillaume/dev/projects/pangolin/";
    pgl::resources::set_root(path);
    const std::string& root = pgl::resources::root();

    ASSERT_EQ(root, "/home/guillaume/dev/projects/pangolin");
  }
}
