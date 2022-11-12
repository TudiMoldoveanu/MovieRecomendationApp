#pragma once
#include <string>
#include <optional>

class UserWatched
{

private:
	std::string m_id; // PK
	std::string m_show_id; // FK

public:
	UserWatched();
	UserWatched(std::string id, std::string show_id);
	~UserWatched();

	void setId(const std::string& m_id);
	void setShowId(const std::string& show_id);

	std::string getId() const;
	std::string getShowId() const;
};

