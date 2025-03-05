//
// Created by Ferit Bilgi on 2.12.2024.
//

#ifndef BILKENTBEATS_H
#define BILKENTBEATS_H

#include <string>
using namespace std;

class BilkentBeats {
public:
    BilkentBeats();
    ~BilkentBeats();

    void addUser(const int userId, const string& userName);
    void removeUser(const int userId);
    void printUsers() const;

    void addSong(const int songId, const string& songName, const string& artist);
    void removeSong(const int songId);
    void printSongs() const;

    void addPlaylist(const int userId, const int playlistId);
    void removePlaylist(const int playlistId, const int songId);
    void addSongToPlaylist(const int playlistId, const int songId);
    void removeSongFromPlaylist(const int playlistId, const int songId);
    void printSongsInPlaylist(const int playlistId) const;

private:
    struct SongNode {
        int id;
        string name;
        string artist;
        SongNode* next;
        SongNode(int id, const string& name, const string& artist);
    };

    struct PlaylistNode {
        int id;
        SongNode* songs;
        PlaylistNode* next;
        PlaylistNode(int id);
    };

    struct UserNode {
        int id;
        string name;
        PlaylistNode* playlists;
        UserNode* next;
        UserNode(int id, const string& name);
    };

    SongNode* songsHead;
    UserNode* usersHead;

    void clearSongs();
    void clearUsers();
    void removeSongsFromPlaylist(int playlistId);
    PlaylistNode* findPlaylist(UserNode* user, int playlistId);
};


#endif //BILKENTBEATS_H
