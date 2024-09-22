SELECT AVG(energy) as average_energy_drake FROM songs
    JOIN artists ON songs.artist_id = artists.id
    WHERE artists.name LIKE "drake%";