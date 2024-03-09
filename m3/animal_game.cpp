/* This program implements the animal game using raw pointers without memory leak.
However, a better practice is to use light weight RAII class, i.e., the unique_ptr, 
for a better object life-time management. */
#include<string>
#include<iostream>
using namespace std;

typedef struct node node;
typedef struct tree tree;

// Implement the game as a binary tree.
struct node
{
    node (string q, bool leaf, string animal): q(q), leaf(leaf), animal(animal) {}
    string q; // The question for this node
    bool leaf; // Check if it is the leaf node
    string animal; // The animal, only valid if it is a leaf node.
    node* left; // A "yes" answer from the user goes to the left branch
    node* right; // A "no" answer from the user goes to the right branch
};

struct tree
{
    tree (node* root): root(root) {}
    node* root;
};

// This function asks questions in each node, dives into one branch according to user's input,
// and iterates till a leaf node.
node* AskQuestions (tree * game) {
    node* cur_node = game->root;
    string user_ans;

    while (! cur_node->leaf) {
        cout << cur_node->q << endl;
        getline(cin, user_ans);
        if (user_ans.compare("yes") == 0) {
            cur_node = cur_node->left;
        } else if (user_ans.compare("no") == 0) {
            cur_node = cur_node->right;
        } else {
            cout << "Please answer yes or no only!" << endl;
            continue;
        }
    }
    return cur_node;
}

// Delete the tree.
void deleteTree(node* node) 
{ 
    if (node->leaf)
    {
        delete node;
        return;
    }
    deleteTree(node->left); 
    deleteTree(node->right);
    delete node;
}

// The animal game.
void AnimalGame () {
    // Initialize the game.
    node* root = new node("Can it fly? (yes/no)", false, "");
    root->left = new node ("Is it a bird? (yes/no)", true, "bird");
    root->right = new node ("Is it a dog? (yes/no)", true, "dog");

    tree game(root);

    // Start playing the game.
    cout << "Welcome to the animal game!" << endl;
    string user_ans;
    for (;;)
    {
        cout << "Think of an animal." << endl;
        // Ask questions.
        node* cur_node = AskQuestions(&game);
        // Guess and update.
        cout << cur_node->q << endl;
        getline(cin, user_ans);

        if (user_ans.compare("yes") == 0) {
            cout << "Cool! I win." << endl;
        } else {
            string animal;
            string question;
            cout << "Oh no I lose! What is the animal?" << endl;
            getline(cin,animal);
            cout << "What is the question that is true for " << animal << " but not for " << cur_node->animal << "?" << endl;
            getline(cin, question);
            cur_node->leaf = false;
            cur_node->q = question;

            cur_node->left = new node ("Is it a " + animal + "?", true, animal);
            cur_node->right = new node ("Is it a " + cur_node->animal + "?", true, cur_node->animal);
        }

        cout << "Do you want to play again? (yes/no/reset)" << endl;
        getline(cin, user_ans);

        if (user_ans.compare("yes") == 0) {
            continue;
        } else if (user_ans.compare("no") == 0){
            deleteTree(root);
   