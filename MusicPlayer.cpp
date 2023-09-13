//
// Created by Ani Hadagali on 13/09/23.
//

#include "MusicPlayer.h"
#include "bits/stdc++.h"
#include <thread>
#include <chrono>

using namespace std;

int currSong = 0;
string songName;
int dur;

MusicPlayer::MusicPlayer(string name) {
    playList_name = name;
    cout << "Playing in Spotify...\n";
}

void MusicPlayer::Pause() {
    paused = true;
}

bool MusicPlayer::Play(std::string name, int time) {
    cout << "Playing " + name << " ";

    for (int i = 0; i < time && !stopped; ++i) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));// Sleep for 1 second
    }

    if(!paused) {
        cout << "Playing next\n";
        currSong++;
        stopped = true;
    }

    return !paused;
}

void MusicPlayer::Spotify() {
    string currPlaylist = playList_name;
    vector<pair<string,int>> songs;

    ifstream openplaylist_file;
    openplaylist_file.open(currPlaylist + ".txt");
    if(openplaylist_file.is_open()) {
        string line;
        while(getline(openplaylist_file,line)) {
            istringstream iss(line);
            string songName;
            string artist;
            string genre;
            string dur;
            iss >> songName >> artist >> genre >> dur;
            int time = stoi(dur);
            songs.emplace_back(songName,time);
        }
        openplaylist_file.close();
    }

    while(true) {
        cout << "1. Play\n2. Pause\n3. Next\n4. Prev\n5. Exit\n";
        cout << "Chose one" << endl;

        int ch;
        cin >> ch;

        switch (ch) {
            case 1: {
                if(songs.empty()) {
                    cout << "There are no songs in your current playlist...\nPlease add songs...";
                    return;
                }
                songName = songs[currSong].first;
                dur = songs[currSong].second;
                Play(songName,dur);
                break;
            }
            case 2: {
                Pause();
                break;
            }
            case 3: {
                currSong = (currSong + 1) % 4;
                songName = songs[currSong].first;
                dur = songs[currSong].second;
                Play(songName,dur);
                break;
            }
            case 4: {
                if(currSong == 0) {
                    currSong = songs.size();
                }
                currSong = (currSong - 1);
                songName = songs[currSong].first;
                dur = songs[currSong].second;
                Play(songName,dur);
                break;
            }
            default: {
                cout << "thank you...\n";
                return;
            }
        }
    }
}