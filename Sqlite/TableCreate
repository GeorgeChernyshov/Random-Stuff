CREATE TABLE Conference(
    name TEXT PRIMARY KEY, 
    description TEXT UNIQUE
);
CREATE TABLE Venue(
    id INTEGER PRIMARY KEY,
    name TEXT UNIQUE,
    city TEXT,
    country TEXT,
    lat NUMERIC(7,5),
    lon NUMERIC(8,5),
    UNIQUE(lat, lon)
);
CREATE TABLE PaperSubmission(
  id INTEGER PRIMARY KEY,
  conference TEXT,
  year INTEGER,
  title TEXT,
  isbn TEXT,
  page INTEGER,
  venue_id INTEGER,
  FOREIGN KEY(conference) REFERENCES Conference(name),
  FOREIGN KEY(venue_id) REFERENCES Venue(id),
  UNIQUE(title, conference, year),
  UNIQUE(isbn, conference, year),
  UNIQUE(page, conference, year)
);
