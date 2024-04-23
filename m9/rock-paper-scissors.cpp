/* 
    A Rock-paper scissors Game.
    Utilize concurrency to ensure two players are playing simultaneously.
*/
#include<iostream>
#include<atomic>
#include <thread>
#include <random>
#include <stdexcept>
#include <thread>
#include <future>
using namespace std;

class player {
    public:
    player() {
        gen = mt19937(rd());
        distrib = uniform_int_distribution<> (1, 3);
    }
    string play(atomic_flag &game_started){
        // Wait for the game to start
        game_started.wait(false);
        // Game starts
        int outcome = distrib(gen);
        switch (outcome)
        {
        case 1:
            return "rock";
        case 2:
            return "paper";
        case 3:
            return "scissors";
        default:
            throw runtime_error("error playing the game");
        }
    }
    random_device rd;  // a seed source for the random number engine
    mt19937 gen;
    uniform_int_distribution<> distrib;
};

// Report the current scores
void report_score(int &p1_score, int &p2_score, int &i, int &round) {
    if (i<round-1) {
        cout << "current score is " << p1_score << ":" << p2_score << endl;
    } else if (i==round-1) {
        cout << "final score is " << p1_score << ":" << p2_score << endl;
        if (p1_score==p2_score) {
            cout << "The game is a draw.";
        } else if (p1_score>p2_score) {
            cout << "p1 is the winner of the game.";
        } else {
            cout << "p2 is the winner of the game.";
        }
    }
}

// Output the winner and update scores
void determine_winner(string &r1, string &r2, int &p1_score, int &p2_score, int &i, int &round){
    if (r1==r2){
        cout << "draw" << endl;
    } else if (r1=="rock") {
        if (r2=="paper"){
            cout << "p2 winned" << endl;
            p2_score+=1;
        } else if (r2=="scissors"){
            cout << "p1 winned" << endl;
            p1_score+=1;
        } else {
            throw runtime_error("game's return is invalid");
        } 
    } else if (r1=="paper") {
        if (r2=="rock"){
            cout << "p1 winned" << endl;
            p1_score+=1;
        } else if (r2=="scissors") {
            cout << "p2 winned" << endl;
            p2_score += 1;
        } else {
            throw runtime_error("game's return is invalid");
        }
    } else if (r1=="scissors") {
        if (r2=="rock") {
            cout << "p2 winned" << endl;
            p2_score+=1;
        } else if (r2=="paper") {
            cout << "p1 winned" << endl;
            p1_score+=1;
        } else {
            throw runtime_error("game's return is invalid");
        }
    } else {
        throw runtime_error("game's return is invalid");
    }
    report_score(p1_score, p2_score, i, round);
}
// Main thread
int main() {
    player p1;
    player p2;
    int p1_score = 0;
    int p2_score = 0;
    atomic_flag game_started;
    game_started.clear();
    int round = 10;

    for (int i = 0; i < round; i++){
        auto f1 = async(&player::play, &p1, ref(game_started));
        auto f2 = async(&player::play, &p2, ref(game_started));
        
        cout<< "Round" << i+1 << ": Rock-Paper-Scissors Go!" << endl;
        game_started.test_and_set();
        game_started.notify_all();

        string r1 = f1.get();
        string r2 = f2.get();
        cout<< "p1 played " << r1 << endl;
        cout<< "p2 played " << r2 << endl;

        determine_winner(r1,r2,p1_score,p2_score,i,round);

        game_started.clear();
    }
    return 0;
}