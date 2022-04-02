// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
using namespace std;

//test empty when empty
TEST(test_empty_impl_1) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
}

//test empty when size == 1
TEST(test_empty_impl_2) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    ASSERT_FALSE(tree.empty());
}

//test empty when size > 1
TEST(test_empty_impl_3) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(8);
    ASSERT_FALSE(tree.empty());
}

//assignment operator when rhs is empty (test destory_nodes and copy_nodes)
TEST(test_assignment_1) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    ASSERT_TRUE(tree.size() != 0);
    
    BinarySearchTree<int> tree0;
    tree = tree0;
    //tree should be empty
    ASSERT_TRUE(tree.size() == 0);
}

//assignment operator when rhs is NOT empty (test destory_nodes and copy_nodes)
TEST(test_assignment_2) {
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


//test empty tree height
TEST(test_height_1) {
    //test empty
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.height(), 0u);
    
}

//test two-branch tree height with some length paths
TEST(test_height_2) {
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

//test single node tree height
TEST(test_height_3) {
    BinarySearchTree<int> tree;
    tree.insert(11);
    ASSERT_TRUE(tree.height() == 1);
}

TEST(test_height_3_1) {
    BinarySearchTree<int> tree;
    tree.insert(11);
    tree.insert(13);
    ASSERT_TRUE(tree.height() == 2);
}

//test one branch tree height 3
TEST(test_height_4) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(11);
    tree.insert(13);
    cout << tree.height() << endl;
    
    ASSERT_TRUE(tree.height() == 3);
}

TEST(test_height_4_1) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(11);
    tree.insert(13);
    tree.insert(14);
    
    ASSERT_TRUE(tree.height() == 4);
}


//test two-branch tree height 3 (longest on left)
TEST(test_height_5) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(8);
    tree.insert(11);
    tree.insert(13);
    ASSERT_TRUE(tree.height() == 3);
}

//test two-branch tree height 3 (longest on right)
TEST(test_height_6) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(10);
    tree.insert(8);
    tree.insert(7);
    tree.insert(6);
    
    ASSERT_TRUE(tree.height() == 4);
}

TEST(test_size_2) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.size() == 0);
    
}


TEST(test_copy_nodes_1) {
    
}

TEST (test_destroy_nodes_1) {
    
}


//find the first item
TEST(test_find_1) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(10);
    tree.insert(8);
    tree.insert(7);
    tree.insert(6);
    
    ASSERT_TRUE(tree.find(9) != tree.end());
}

//find the only item
TEST(test_find_2) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    
    ASSERT_TRUE(tree.find(9) != tree.end());
}

//find the second item
TEST(test_find_3) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(10);
    
    ASSERT_TRUE(tree.find(10) != tree.end());
}

TEST(test_find_4) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(10);
    tree.insert(8);
    
    ASSERT_TRUE(tree.find(8) != tree.end());
}

//fail at finding an item that isn't there
TEST(test_find_5) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(10);
    tree.insert(8);
    
    ASSERT_TRUE(tree.find(50) == tree.end());
}

TEST(test_insert_1) {

}

TEST(test_min_element_1) {
    
}

TEST(test_max_element_1) {
    
}

//test sorting invariant with empty tree
TEST(test_sorting_invariant_0) {
    BinarySearchTree<int> b;
   
    ASSERT_TRUE(b.check_sorting_invariant());
}

//test sorting invariant with root node and a node to the left, then break it
TEST(test_sorting_invariant_1) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}





//test sorting invariant with root node and a node to the left
TEST(test_sorting_invariant_3) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    
    ASSERT_TRUE(b.check_sorting_invariant());
}

//test sorting invariant with root node and node to the right
TEST(test_sorting_invariant_4) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(2);
    
    ASSERT_TRUE(b.check_sorting_invariant());
}

//test sorting invariant with just a root node
TEST(test_sorting_invariant_5) {
    BinarySearchTree<int> b;
    b.insert(1);
    
    ASSERT_TRUE(b.check_sorting_invariant());
}

//test sorting invariant with complicated branches sorted
TEST(test_sorting_invariant_6) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(2);
    b.insert(4);
    b.insert(0);
    b.insert(3);
    b.insert(-1);
    
    ASSERT_TRUE(b.check_sorting_invariant());
}

//test sorting invariant with branch sorted, but whole tree not sorted
TEST(test_sorting_invariant_7) {
    BinarySearchTree<int> b;
    b.insert(3);
    b.insert(1);
    b.insert(0);
    b.insert(5);
    b.insert(4);
    b.insert(6);
    *b.find(4) = 2;
    
    
    ASSERT_FALSE(b.check_sorting_invariant());
    //WE HAVE A BUG
}



TEST(test_traverse_order_1) {
    
}

TEST(test_traverse_preorder_1) {
    
}

TEST(test_min_greater_than_1) {
    
}

TEST_MAIN()
