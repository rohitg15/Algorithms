#include<stdio.h>
#include<stdlib.h>

/* This is the structure defining the node */

struct node
{

	int x;
	node *left,*right;
};

/* Given an Integer value, create a new node */
node* create_node(int val)
{
	node *n = (node*)malloc(sizeof(node));
	n->x = val;
	n->left = NULL;
	n->right = NULL;
	return n;
	
}


/* using post order traversal to deallocate the tree from the heap  */

void post_order_delete(node *root)
{
	if (root == NULL)
	  {
            return ;
	  }
	if (root->left)
	  {
	    post_order_delete(root->left);
	  }
	if (root->right)
	  {
	    post_order_delete(root->right);
	  }
	
	//Delete the current node
	free(root);

}

node* least_common_ancestor(node *root,int &a,int &b)
{
  if (root == NULL)
    {
      return NULL;
    }
  if (root->x == a || root->x == b)
    {
      return root;
    }

  /* recursively search the left and rigt subtrees  */
  node *left = least_common_ancestor(root->left,a,b);
  node *right = least_common_ancestor(root->right,a,b);
  /* at this point, if both the left and right node* are set, then the root will be the Least Common Ancestor
     So return this value
   */
  if (left && right)
    {
      return root;
    }

  /* If at this point, atleast one out of left and right is NULL, then return the non-NULL value as the LCA
     If both of them are NULL then return NULL - there is no LCA (which means that atleast one of the nodes
     did not belong to the tree)
  */

  return (left)?left:right;
 
}

int main(int argc,char* argv[])
{


  node *root = create_node(1);
  root->left = create_node(2);
  root->right = create_node(3);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->right->left = create_node(6);
  root->right->right = create_node(7);


  int x = 4, y = 7;
  node *lca = least_common_ancestor(root,x,y);

  if (lca)
    {
      printf("lca of %d,%d is %d\n",x,y,lca->x);
    }
  else
    {
      printf("atleast one of the nodes among %d,%d was not found in the tree rooted at %d\n",x,y,root->x);
    }

  post_order_delete(root);

	return 0;
}
