#include "List.h"
#include "tweet.h"

int main()
{
    List<tweet> Tweets;
    std::string Text;

    Tweets.format("Tweet\n--->\n", "\n", "\n--->\n");
    while (true)
    {
        std::cout << "\nNachricht: ";
        std::getline(std::cin, Text);
        if (Text == "quit") break;
        Tweets.insertFront(tweet(Text));

        std::cout << Tweets;
    }
}