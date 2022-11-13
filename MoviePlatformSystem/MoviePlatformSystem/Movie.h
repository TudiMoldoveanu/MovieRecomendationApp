#pragma once
#define SQLITE_ORM_OPTIONAL_SUPPORTED
#define SQLITE_ORM_OMITS_CODECVT
#include <optional>
#include <string>

class Movie
{
	std::string m_showId; //PK
	std::optional<std::string> m_type;
	std::optional<std::string> m_title;
	std::optional<std::string> m_director;
	std::optional<std::string> m_cast;
	std::optional<std::string> m_country;
	std::optional<std::string> m_dateAdded;
	std::optional<std::string> m_releaseYear;
	std::optional<std::string> m_rating;
	std::optional<std::string> m_duration;
	std::optional<std::string> m_listedIn;
	std::optional<std::string> m_description;

public:
	Movie();
	Movie(std::string showId, std::optional<std::string> type, std::optional<std::string> title, std::optional<std::string> director,
		std::optional<std::string> cast, std::optional<std::string> country, std::optional<std::string> dateAdded,
		std::optional<std::string> releaseYear, std::optional<std::string> rating, std::optional<std::string> duration,
		std::optional<std::string> listedIn, std::optional<std::string> description);
	~Movie();

	void setId(const std::string& showId);
	void setType(const std::optional<std::string>& type);
	void setTitle(const std::optional<std::string>& title);
	void setDirector(const std::optional<std::string>& director);
	void setCast(const std::optional<std::string>& cast);
	void setCountry(const std::optional<std::string>& country);
	void setDateAdded(const std::optional<std::string>& dateAdded);
	void setReleaseYear(const std::optional<std::string>& releaseYear);
	void setRating(const std::optional<std::string>& rating);
	void setDuration(const std::optional<std::string>& duration);
	void setListedIn(const std::optional<std::string>& listedIn);
	void setDescription(const std::optional<std::string>& description);

	std::string getId() const;
	std::optional<std::string> getType() const;
	std::optional<std::string> getTitle() const;
	std::optional<std::string> getDirector() const;
	std::optional<std::string> getCast() const;
	std::optional<std::string> getCountry() const;
	std::optional<std::string> getDateAdded() const;
	std::optional<std::string> getReleaseYear() const;
	std::optional<std::string> getRating() const;
	std::optional<std::string> getDuration() const;
	std::optional<std::string> getListedIn() const;
	std::optional<std::string> getDescription() const;

};
