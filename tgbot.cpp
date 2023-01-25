#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include "image_storage.h"
#include "leaderboard.h"
#include <tgbot/tgbot.h>
#include <fstream>

int main() {
    std::string token("5983544311:AAH04sQSLZqmkLBOLY4iHuP8Xu1kW1pngi8");
    bool photo_ch = false;
    int lead_ch = 0;
    int photo_num = 0;
    int type = 0;
    ImageStorage img_st;
    Leaderboard lead;
    std::vector<std::string> commands {"/start", "/photo", "/top"};

    std::vector<std::string> ans(9, "");
    for (int i = 1; i <= 9; i++) {
        std::ifstream in("../message_text/" + std::to_string(i) + ".txt", std::ios::binary);
        while (in) {
            std::string s;
            getline(in, s);
            if ((i == 4) || (i == 5) || (i == 8))
                ans[i - 1] += s;
            else
                ans[i - 1] += s + '\n';
        }
        in.close();
    }

    TgBot::Bot bot(token);
    bot.getEvents().onCommand("start", [&bot, &ans](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, ans[0]);
        std::cout << (message->from->username != "" ? message->from->username : std::to_string(message->from->id)) << '\n';
//        std::cout << "Привет! Я бот для сбора датасета.\nЧтобы отправить мне фотографии, используйте команду '/photo'.\nЧтобы увидеть таблицу лидеров, используйте команду '/top'" << '\n';
    });
    bot.getEvents().onCommand("photo", [&bot, &photo_ch, &ans](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, ans[1]);
        photo_ch = true;
    });
    bot.getEvents().onCommand("top", [&bot, &lead_ch, &ans](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, ans[2]);
        lead_ch = 1;
    });
    bot.getEvents().onAnyMessage([&photo_num, &bot, &img_st, &photo_ch, &lead, &lead_ch, &type, &commands, &ans](TgBot::Message::Ptr message) {
        if (photo_ch) {
            if (message->text == "/end") {
                bot.getApi().sendMessage(message->chat->id, ans[3] + std::to_string(photo_num));
                lead.update((message->from->username != "" ? message->from->username : std::to_string(message->from->id)), photo_num);
                photo_ch = false;
                photo_num = 0;
            }
            else {
                try {
                    auto mess = message->document;
                    if (!mess)
                        throw std::invalid_argument("");
//                    std::cout << message->document->fileId << '\n';
                    auto photo = bot.getApi().getFile(message->document->fileId);
                    std::string f_str = bot.getApi().downloadFile(photo->filePath);
                    int res = img_st.add((message->from->username!="" ? message->from->username : std::to_string(message->from->id)), f_str);
                    if (res == 0)
                        photo_num++;
                }
                catch (...) {
                    bot.getApi().sendMessage(message->chat->id, ans[4] + std::to_string(photo_num));
                    photo_ch = false;
                    photo_num = 0;
                }
            }
        }
        else if (lead_ch == 1) {
            try {
                type = std::stoi(message->text);
                bot.getApi().sendMessage(message->chat->id, ans[5]);
                lead_ch = 2;
                return;
            }
            catch (...) {
                bot.getApi().sendMessage(message->chat->id, ans[6]);
                lead_ch = false;
            }
        }
        else if (lead_ch == 2) {
            try {
                int num = std::stoi(message->text);
                std::vector<std::pair<std::string, int>> list;
                lead.top(num, list, type);
                std::string list_s = ans[7];
                for (auto k : list) {
                    list_s += k.first + ": " + std::to_string(k.second) + "\n";
                }
                bot.getApi().sendMessage(message->chat->id, list_s);
                lead_ch = false;
            }
            catch (...) {
                bot.getApi().sendMessage(message->chat->id, ans[6]);
                lead_ch = false;
            }
        }
        else {
            for (auto i : commands)
                if (i == message->text)
                    return;
            bot.getApi().sendMessage(message->chat->id, ans[8]);
        }
    });

    try {
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (std::exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
