SELECT songs.name from songs, artists WHERE artists.id = songs.artist_id AND artists.name LIKE '%malone';