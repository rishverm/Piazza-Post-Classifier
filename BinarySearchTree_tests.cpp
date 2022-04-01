// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
/*
TEST(test_destroy) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    ASSERT_TRUE(tree.size() != 0);
    
    BinarySearchTree<int> tree0;
    tree = tree0;
    //tree should be empty
    ASSERT_TRUE(tree.size() == 0);
}


TEST(test_size_1) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    ASSERT_TRUE(tree.size() != 0);
    
}
*/

TEST(test_height_and_destructor) {
    BinarySearchTree<int> tree;
    
    tree.insert(11);
    tree.insert(9);
    tree.insert(13);
    
    ASSERT_TRUE(tree.height() == 2);
}
    

TEST(test_height_and_assignment_operator) {
    BinarySearchTree<int> tree;
    
    tree.insert(11);
    tree.insert(9);
    tree.insert(13);
    
    ASSERT_TRUE(tree.height() == 2);
    
    BinarySearchTree<int> tree0;
    tree0.insert(5);
    tree = tree0;
    //tree should be empty
    ASSERT_TRUE(tree.size() == 1);
    
  
}
/*
TEST(test_height_1) {
    BinarySearchTree<int> tree;
    
    tree.insert(11);
    tree.insert(9);
    tree.insert(13);
    
    ASSERT_TRUE(tree.height() == 2);
    
    BinarySearchTree<int> tree0;
    tree = tree0;
    //tree should be empty
    ASSERT_TRUE(tree.size() == 0);
    
  
}




TEST(test_size_2) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.size() == 0);
    
}


TEST(test_height_2) {
    //test empty
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.height(), 0u);
    
}


TEST(test_copy_nodes_1) {
    
}

TEST (test_destroy_nodes_1) {
    
}

TEST(test_find_1) {
    
}

TEST(test_insert_1) {

}

TEST(test_min_element_1) {
    
}

TEST(test_max_element_1) {
    
}

TEST(test_sorting_invariant_1) {
    
}

TEST(test_traverse_order_1) {
    
}

TEST(test_traverse_preorder_1) {
    
}

TEST(test_min_greater_than_1) {
    
}
*/
TEST_MAIN()
