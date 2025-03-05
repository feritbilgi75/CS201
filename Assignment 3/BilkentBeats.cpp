//
// Created by Ferit Bilgi on 2.12.2024.

#include "BilkentBeats.h"
#include <iostream>

using namespace std;

BilkentBeats::SongNode::SongNode(int id, const string &name, const string &artist) {
    this->id = id;
    this->name = name;
    this->artist = artist;
    next = nullptr;
}

BilkentBeats::PlaylistNode::PlaylistNode(int id) {
    this->id = id;
    next = nullptr;
    songs = nullptr;
}

BilkentBeats::UserNode::UserNode(int id, const string &name) {
    this->id = id;
    this->name = name;
    playlists = nullptr;
    next = nullptr;
}

BilkentBeats::BilkentBeats() {
    songsHead = nullptr;
    usersHead = nullptr;
}

BilkentBeats::~BilkentBeats() {
    clearSongs();
    clearUsers();
}

void BilkentBeats::addUser(const int userId, const string &userName) {
    UserNode* newNode = new UserNode(userId, userName);
    if (!usersHead || userId < usersHead->id) {
        newNode->next = usersHead;
        usersHead = newNode;
        cout << "Added user " << userId << "." <<endl;
        return;
    }

    UserNode* prev = nullptr;
    UserNode* curr = usersHead;
    while(curr && curr->id < userId) {
        prev = curr;
        curr = curr->next;
    }
    if (curr && curr->id == userId) {
        cout << "Cannot add user. There is already a user with ID " << userId << "." << endl;
        delete newNode;
        return;
    }

    prev->next = newNode;
    newNode->next = curr;
    cout << "Added user " << userId << "." << endl;

}

void BilkentBeats::removeUser(const int userId) {
    if (!usersHead) {
        cout << "Cannot remove user. There is no user with ID " << userId << endl;
        return;
    }

    if (usersHead->id == userId) {
        UserNode* toDelete = usersHead;
        usersHead = usersHead->next;

        while (toDelete->playlists) {
            PlaylistNode* tempPlaylist = toDelete->playlists;
            toDelete->playlists = toDelete->playlists->next;

            while (tempPlaylist->songs) {
                SongNode* tempSong = tempPlaylist->songs;
                tempPlaylist->songs = tempPlaylist->songs->next;
                delete tempSong;
            }

            delete tempPlaylist;
        }

        delete toDelete;
        cout << "Removed user " << userId << "." << endl;
        return;
    }

    UserNode* curr = usersHead;
    UserNode* prev = nullptr;

    while (curr && curr->id != userId) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Cannot remove user. There is no user with ID " << userId << "." << endl;
        return;
    }

    prev->next = curr->next;

    while (curr->playlists) {
        PlaylistNode* tempPlaylist = curr->playlists;
        curr->playlists = curr->playlists->next;

        while (tempPlaylist->songs) {
            SongNode* tempSong = tempPlaylist->songs;
            tempPlaylist->songs = tempPlaylist->songs->next;
            delete tempSong;
        }

        delete tempPlaylist;
    }

    delete curr;
    cout << "Removed user " << userId << "." << endl;
}


void BilkentBeats::printUsers() const{
    if (!usersHead) {
        cout << "There are no users to show." << endl;
        return;
    }
    cout << "Users in the system:" << endl;
    UserNode* curr = usersHead;
    while(curr) {
        cout << "User ID : " << curr->id << ", Name : " << curr->name;
        if(!curr->playlists) {
            cout << ", Playlist IDs : None" << endl;
        } else {
            cout << ", Playlist IDs : [";
            PlaylistNode* pCurr = curr->playlists;
            while(pCurr) {
                cout << pCurr->id;
                if(pCurr->next) {
                    cout << ",";
                }
                pCurr = pCurr->next;
            }
            cout << "]" << endl;
        }
        curr = curr->next;
    }

}

void BilkentBeats::clearSongs() {
    while (songsHead) {
        SongNode* temp = songsHead;
        songsHead = songsHead->next;
        delete temp;
    }
}


void BilkentBeats::clearUsers() {
    while (usersHead) {
        UserNode* temp = usersHead;
        usersHead = usersHead->next;

        while (temp->playlists) {
            PlaylistNode* tempPlaylist = temp->playlists;
            temp->playlists = temp->playlists->next;

            while (tempPlaylist->songs) {
                SongNode* tempSong = tempPlaylist->songs;
                tempPlaylist->songs = tempPlaylist->songs->next;
                delete tempSong;
            }

            delete tempPlaylist;
        }

        delete temp;
    }
}



void BilkentBeats::removePlaylist(const int userId, const int playListId) {
    if (!usersHead) {
        cout << "Cannot remove playlist. There is no user with ID " << userId << "." << endl;
        return;
    }

    UserNode* user = usersHead;
    while (user && user->id != userId) {
        user = user->next;
    }

    if (!user) {
        cout << "Cannot remove playlist. There is no user with ID " << userId << "." << endl;
        return;
    }

    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = user->playlists;

    while (curr && curr->id != playListId) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Cannot remove playlist. User " << userId << " does not have a playlist with ID " << playListId << "." << endl;
        return;
    }

    if (prev) {
        prev->next = curr->next;
    } else {
        user->playlists = curr->next;
    }

    while (curr->songs) {
        SongNode* tempSong = curr->songs;
        curr->songs = curr->songs->next;
        delete tempSong;
    }

    delete curr;

    cout << "Removed playlist " << playListId << " from user " << userId << "." << endl;
}



void BilkentBeats::removeSongFromPlaylist(const int playlistId, const int songId) {
    UserNode* user = usersHead;

    while (user) {
        PlaylistNode* playlist = user->playlists;

        while (playlist) {
            if (playlist->id == playlistId) {
                SongNode* prev = nullptr;
                SongNode* curr = playlist->songs;

                while (curr) {
                    if (curr->id == songId) {
                        if (prev) {
                            prev->next = curr->next;
                        } else {
                            playlist->songs = curr->next;
                        }

                        delete curr;
                        cout << "Removed song " << songId << " from playlist " << playlistId << "." <<endl;
                        return;
                    }
                    prev = curr;
                    curr = curr->next;
                }

                cout << "Cannot remove song. There is no song " << songId << " in playlist " << playlistId << "." << endl;
                return;
            }
            playlist = playlist->next;
        }
        user = user->next;
    }

    cout << "Cannot remove song. There is no playlist with ID " << playlistId << "." << endl;
}

void BilkentBeats::removeSong(const int songId) {
    if (!songsHead) {
        cout << "Cannot remove song. There is no song with ID " << songId << ".\n";
        return;
    }

    SongNode* prev = nullptr;
    SongNode* curr = songsHead;

    while (curr && curr->id != songId) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Cannot remove song. There is no song with ID " << songId << ".\n";
        return;
    }

    if (prev) {
        prev->next = curr->next;
    } else {
        songsHead = curr->next;
    }

    delete curr;

    UserNode* user = usersHead;
    while (user) {
        PlaylistNode* playlist = user->playlists;
        while (playlist) {
            SongNode* prevSong = nullptr;
            SongNode* song = playlist->songs;
            while (song) {
                if (song->id == songId) {
                    if (prevSong) {
                        prevSong->next = song->next;
                    } else {
                        playlist->songs = song->next;
                    }
                    delete song;
                    break;
                }
                prevSong = song;
                song = song->next;
            }
            playlist = playlist->next;
        }
        user = user->next;
    }

    cout << "Removed song " << songId << ".\n";
}

void BilkentBeats::addPlaylist(const int userId, const int playlistId) {
    UserNode* user = usersHead;

    while (user && user->id != userId) {
        user = user->next;
    }

    if (!user) {
        cout << "Cannot add playlist. There is no user with ID " << userId << ".\n";
        return;
    }

    UserNode* tempUser = usersHead;
    while (tempUser) {
        PlaylistNode* playlist = tempUser->playlists;
        while (playlist) {
            if (playlist->id == playlistId) {
                cout << "Cannot add playlist. There is a user having a playlist with ID " << playlistId << ".\n";
                return;
            }
            playlist = playlist->next;
        }
        tempUser = tempUser->next;
    }

    PlaylistNode* newPlaylist = new PlaylistNode(playlistId);
    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = user->playlists;

    while (curr && curr->id < playlistId) {
        prev = curr;
        curr = curr->next;
    }

    if (!prev) {
        newPlaylist->next = user->playlists;
        user->playlists = newPlaylist;
    } else {
        prev->next = newPlaylist;
        newPlaylist->next = curr;
    }

    cout << "Added playlist " << playlistId << " to user " << userId << ".\n";
}


void BilkentBeats::addSongToPlaylist(const int playlistId, const int songId) {
    SongNode* song = songsHead;
    while (song && song->id != songId) {
        song = song->next;
    }

    if (!song) {
        cout << "Cannot add song. There is no song with ID " << songId << ".\n";
        return;
    }

    UserNode* user = usersHead;
    while (user) {
        PlaylistNode* playlist = user->playlists;

        while (playlist) {
            if (playlist->id == playlistId) {
                SongNode* playlistSong = playlist->songs;
                while (playlistSong) {
                    if (playlistSong->id == songId) {
                        cout << "Cannot add song. The playlist already contains song " << songId << ".\n";
                        return;
                    }
                    playlistSong = playlistSong->next;
                }

                SongNode* newSong = new SongNode(songId, song->name, song->artist);
                if (!playlist->songs) {
                    playlist->songs = newSong;
                } else {
                    SongNode* tail = playlist->songs;
                    while (tail->next) {
                        tail = tail->next;
                    }
                    tail->next = newSong;
                }

                cout << "Added song " << songId << " to playlist " << playlistId << ".\n";
                return;
            }
            playlist = playlist->next;
        }
        user = user->next;
    }

    cout << "Cannot add song. There is no playlist with ID " << playlistId << ".\n";
}


void BilkentBeats::addSong(const int songId, const std::string& songName, const std::string& artists) {
    SongNode* newSong = new SongNode(songId, songName, artists);

    if (!songsHead || songId < songsHead->id) {
        newSong->next = songsHead;
        songsHead = newSong;
        cout << "Added song " << songId << ".\n";
        return;
    }

    SongNode* prev = nullptr;
    SongNode* curr = songsHead;

    while (curr && songId > curr->id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->id == songId) {
        cout << "Cannot add song. BilkentBeats already contains song " << songId << ".\n";
        delete newSong;
        return;
    }

    prev->next = newSong;
    newSong->next = curr;

    cout << "Added song " << songId << ".\n";
}


void BilkentBeats::printSongs() const {
    if (!songsHead) {
        cout << "Cannot print songs. There is no song in the music library.\n";
        return;
    }

    std::cout << "Music Library:\n";
    SongNode* curr = songsHead;
    while (curr) {
        cout << "Song " << curr->id << " : " << curr->name << " - " << curr->artist << "\n";
        curr = curr->next;
    }
}


void BilkentBeats::printSongsInPlaylist(const int playlistId) const {
    UserNode* user = usersHead;

    while (user) {
        PlaylistNode* playlist = user->playlists;

        while (playlist) {
            if (playlist->id == playlistId) {
                if (!playlist->songs) {
                    cout << "There are no songs to show in playlist " << playlistId << ".\n";
                    return;
                }

                cout << "Songs in playlist " << playlistId << ":\n";
                SongNode* song = playlist->songs;

                while (song) {
                    cout << "Song " << song->id << " : " << song->name << " - " << song->artist << "\n";
                    song = song->next;
                }
                return;
            }
            playlist = playlist->next;
        }
        user = user->next;
    }

    cout << "Cannot print songs. There is no playlist with ID " << playlistId << ".\n";
}

