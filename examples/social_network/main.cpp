
#include <iostream>
#include <graaflib/algorithm/social_network.h>


int main() {
    // Create a graph to represent the social network
    Graaf::Graph socialNetwork;

    // Add nodes for users in the social network
    Graaf::Node userAlice = socialNetwork.addNode("Alice");
    Graaf::Node userBob = socialNetwork.addNode("Bob");
    Graaf::Node userCharlie = socialNetwork.addNode("Charlie");

    // Add edges to represent connections (friendships) between users
    socialNetwork.addEdge(userAlice, userBob);
    socialNetwork.addEdge(userBob, userCharlie);

    // Perform social network analysis using Graaf library
    // You can add relevant algorithms or queries here

    // Print the social network graph
    std::cout << "Social Network Graph:\n";
    for (const Graaf::Node& node : socialNetwork.getNodes()) {
        std::cout << "User: " << socialNetwork.getNodeName(node) << " is connected to: ";
        for (const Graaf::Edge& edge : socialNetwork.getOutgoingEdges(node)) {
            std::cout << socialNetwork.getNodeName(socialNetwork.target(edge)) << " ";
        }
        std::cout << "\n";
    }

    // You can add more social network analysis code here

    return 0;
}
