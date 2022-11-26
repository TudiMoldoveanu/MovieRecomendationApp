#include "Movie.h"

Movie::Movie() {}

Movie::Movie(std::string showId, std::optional<std::string> type, std::optional<std::string> title, std::optional<std::string> director,
    std::optional<std::string> cast, std::optional<std::string> country, std::optional<std::string> dateAdded,
    std::optional<std::string> releaseYear, std::optional<std::string> rating, std::optional<std::string> duration,
    std::optional<std::string> listedIn, std::optional<std::string> description)
    : m_showId{ std::move(showId) }, m_type{ std::move(type) }, m_title{ std::move(title) },
    m_director{ std::move(director) }, m_cast{ std::move(cast) }, m_country{ std::move(country) },
    m_dateAdded{ std::move(dateAdded) }, m_releaseYear{ std::move(releaseYear) }, m_rating{ std::move(rating) },
    m_duration{ std::move(duration) }, m_listedIn{ std::move(listedIn) }, m_description{ std::move(description) } {}

Movie::~Movie() {}

void Movie::setId(std::string showId) {
    m_showId = std::move(showId);
}


void Movie::setType(std::optional<std::string> type) {
    m_type = std::move(type);
}


void Movie::setTitle(std::optional<std::string> title) {
    m_title = std::move(title);
}

void Movie::setDirector(std::optional<std::string> director) {
    m_director = std::move(director);
}


void Movie::setCast(std::optional<std::string> cast) {
    m_cast = std::move(cast);
}

void Movie::setCountry(std::optional<std::string> country) {
    m_country = std::move(country);
}


void Movie::setDateAdded(std::optional<std::string> dateAdded) {
    m_dateAdded = std::move(dateAdded);
}


void Movie::setReleaseYear(std::optional<std::string> releaseYear) {
    m_releaseYear = std::move(releaseYear);
}

void Movie::setRating(std::optional<std::string> rating) {
    m_rating = std::move(rating);
}


void Movie::setDuration(std::optional<std::string> duration) {
    m_duration = std::move(duration);
}


void Movie::setListedIn(std::optional<std::string> listedIn) {
    m_listedIn = std::move(listedIn);
}


void Movie::setDescription(std::optional<std::string> description) {
    m_description = std::move(description);
}

std::string Movie::getId() const
{
    return m_showId;
}

std::optional<std::string> Movie::getType() const {
    return m_type;
}

std::optional<std::string> Movie::getTitle() const {
    return m_title;
}

std::optional<std::string> Movie::getDirector() const {
    return m_director;
}

std::optional<std::string> Movie::getCast() const {
    return m_cast;
}

std::optional<std::string> Movie::getCountry() const {
    return m_country;
}

std::optional<std::string> Movie::getDateAdded() const {
    return m_dateAdded;
}

std::optional<std::string> Movie::getReleaseYear() const {
    return m_releaseYear;
}

std::optional<std::string> Movie::getRating() const {
    return m_rating;
}

std::optional<std::string> Movie::getDuration() const {
    return m_duration;
}

std::optional<std::string> Movie::getListedIn() const {
    return m_listedIn;
}

std::optional<std::string> Movie::getDescription() const {
    return m_description;
}