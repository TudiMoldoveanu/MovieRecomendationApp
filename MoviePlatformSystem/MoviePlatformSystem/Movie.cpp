#include "Movie.h"

Movie::Movie() {}

Movie::Movie(std::string show_id, std::optional<std::string> type, std::optional<std::string> title, std::optional<std::string> director,
    std::optional<std::string> cast, std::optional<std::string> country, std::optional<std::string> date_added,
    std::optional<std::string> release_year, std::optional<std::string> rating, std::optional<std::string> duration,
    std::optional<std::string> listed_in, std::optional<std::string> description)
    : m_show_id{ std::move(show_id) }, m_type{ std::move(type) }, m_title{ std::move(title) },
    m_director{ std::move(director) }, m_cast{ std::move(cast) }, m_country{ std::move(country) },
    m_date_added{ std::move(date_added) }, m_release_year{ std::move(release_year) }, m_rating{ std::move(rating) },
    m_duration{ std::move(duration) }, m_listed_in{ std::move(listed_in) }, m_description{ std::move(description) } {}

Movie::~Movie() {}

void Movie::setId(const std::string& show_id) {
    m_show_id = std::move(show_id);
}


void Movie::setType(const std::optional<std::string>& type) {
    m_type = std::move(type);
}


void Movie::setTitle(const std::optional<std::string>& title) {
    m_title = std::move(title);
}

void Movie::setDirector(const std::optional<std::string>& director) {
    m_director = std::move(director);
}


void Movie::setCast(const std::optional<std::string>& cast) {
    m_cast = std::move(cast);
}

void Movie::setCountry(const std::optional<std::string>& country) {
    m_country = std::move(country);
}


void Movie::setDateAdded(const std::optional<std::string>& date_added) {
    m_date_added = std::move(date_added);
}


void Movie::setReleaseYear(const std::optional<std::string>& release_year) {
    m_release_year = std::move(release_year);
}

void Movie::setRating(const std::optional<std::string>& rating) {
    m_rating = std::move(rating);
}


void Movie::setDuration(const std::optional<std::string>& duration) {
    m_duration = std::move(duration);
}


void Movie::setListedIn(const std::optional<std::string>& listed_in) {
    m_listed_in = std::move(listed_in);
}


void Movie::setDescription(const std::optional<std::string>& description) {
    m_description = std::move(description);
}

std::string Movie::getId() const
{
    return m_show_id;
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
    return m_date_added;
}

std::optional<std::string> Movie::getReleaseYear() const {
    return m_release_year;
}

std::optional<std::string> Movie::getRating() const {
    return m_rating;
}

std::optional<std::string> Movie::getDuration() const {
    return m_duration;
}

std::optional<std::string> Movie::getListedIn() const {
    return m_listed_in;
}

std::optional<std::string> Movie::getDescription() const {
    return m_description;
}