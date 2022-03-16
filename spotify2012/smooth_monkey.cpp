// Smooth Monkey
// Spotify Code Quest 2012
// Problem: https://open.kattis.com/problems/monkey

// Solution Explanation
// When I first attempted this problem back in 2012 it stumped me, but it also interested me enough to re-attempt it 10 years later.
// This time around the solution came to me pretty quickly, so it's comforting to know I've outgrown my past self.

// When first looking at the problem, my instinct was that there must be some "optimal" way to transport and leave smoothie throughout the journey
// such that you end up with a maximal amount at the end. Maybe it was half the distance of your capacity, or maybe some specific fraction of it
// based on the amount present and the distance you have left.
// At this point my 2012 self had no idea how to begin proving what way was best, and I ended up moving on to other problems in the competition.

// Since then my problem solving skills have improved, and I've learned to take different approaches. One important thing I was taught was to
// consider a simpler form of a problem, or to look at just the first step. There might be insight to draw from examining these simpler situations.

// In this case, I took the first example input given and looked at how I could transport my entire stockpile of smoothie one step further into the forest.
// My reasoning was that to make any meaningful progress, we would probably want to have the entire stockpile coming with us. It's possible there might be
// some situation where we want to leave some behind, but I decided to defer that idea for later.

// After mapping out various distances, and seeing how much smoothie I had left at each point, I noticed something. The amount of smoothie missing was
// directly proportional to the distance the monkey had gone. It didn't matter how far we had traveled for the first batch, we always drank at the same rate.
// In the specific case of the first example, she consumed 5 units of smoothie per distance traveled.

// The reason for this is a simple conclusion to reach; with a stockpile of 3000, and a capacity of 1000, there are 3 loads of smoothie to transport.
// However on the final trip, you don't have to go back to the start. So, the rate of consumption can be generalized to ((# of trips * 2) - 1).
// The realization of the rate of consumption being the same no matter what distance she traveled was also important;
// this meant that there were no "optimal distances" that we needed to travel. We just treat the problem like we're moving all the smoothie at once.

// The next thought to enter my head was that as our smoothie supply diminishes, the number of trips we need to make to transport the stockpile also lessens.
// After our stockpile hits 2000 in the first example, we require one less trip. So, our rate of consumption goes from 5 to 3.
// This, combined with the idea that we can make "micro trips" the entire journey, led me to believe this was just a simple rate problem with breakpoints along the way.
// At this point I was pretty convinced this was the core set of ideas needed to solve the problem. So, I tried it on the first example.

// I calculated the distances traveled in each leg based on the rate of consumption and smoothie left, and sure enough, I ended up with the 533.33333333 amount at the end.
// I considered other interesting cases like "what if we don't start out with a multiple of our capacity?",
// but none of them added complexity that felt like the problem could not be solved through this approach.

// I coded it up, and I think I'm satisfied with the results. The next thing to do would be to figure out if there's a more clever way to get the answer.
// Right now it is being solved through a loop until completion, but there might be a mathematical approach to get the answer immediately.

// And there it is, a problem I've thought about on and off 10 years that I solved in 20 minutes when I actually put my mind to it.
// There's probably a life lesson to learn in here somewhere.

#include <stdio.h>
#include <iostream>
using namespace std;

void RunLeg(double &dist_rem, double &smooth_rem, const double capacity);

int main() {

    double distance, stockpile, capacity;
    double delivered;

    cout << "Enter problem constraints (Distance, Stockpile, Capacity)" << endl;
    cin >> distance;
    cin >> stockpile;
    cin >> capacity;
    cout << endl;

    // Check edge cases
    if (distance > stockpile) {
        delivered = 0;
    } else {
        while (distance != 0 && stockpile != 0) RunLeg(distance, stockpile, capacity);
    }

    if (distance != 0) {
        cout << "Monkey did not make it" << endl;
    }
    return 0;
}

void RunLeg(double &dist_rem, double &smooth_rem, const double capacity) {

    // Calculate our rate based on smoothie remaining
    // Then calculate the distance until the next breakpoint
    // Check to see if we reached the end, if not deduct the distance and the smoothie and return.

    int unscaled_rate = (int)((smooth_rem - 1) / capacity);
    int rate = (2 * unscaled_rate) + 1;

    double smooth_tar = capacity * unscaled_rate;
    double distance_traveled = (smooth_rem - smooth_tar) / rate;
    
    cout << "Leg Calculations" << endl;
    cout << "Unscaled Rate: " << unscaled_rate << endl;
    cout << "Rate: " << rate << endl;
    cout << "Smoothie Target: " << smooth_tar << endl;
    cout << "Distance Travelable: " << distance_traveled << endl << endl;

    if (distance_traveled > dist_rem) {
        // Monkey made it
        cout << "Distance remaining (" << dist_rem << ") is less than distance travelable (" << distance_traveled << ")" << endl;
        smooth_rem -= dist_rem * rate;
        dist_rem = 0;
        cout << "Monkey made it, smoothie remaining: " << smooth_rem << endl;
        return;
    } else {
        dist_rem -= distance_traveled;
        smooth_rem = smooth_tar;
    }

    cout << "Loop results: Distance traveled - " << distance_traveled << " Smoothie left - " << smooth_rem << endl << endl;

    return;
}