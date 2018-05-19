#pragma once
#include "TagManager.hpp"


namespace tag::manager {

	class TagManagerFactory {
	public:
		virtual ~TagManagerFactory() noexcept;
		virtual SharedTagManager create(const fs::path &path) const;
	};




	class SharedConfigTagManagerFactory : public TagManagerFactory {
	public:
		explicit SharedConfigTagManagerFactory(const TagConfiguration &configuration = TagConfiguration());
		virtual ~SharedConfigTagManagerFactory() noexcept;
		virtual SharedTagManager create(const fs::path &path) const override;

		const TagConfiguration& getConfiguration() const;
		TagConfiguration& getConfiguration();
		void setConfiguration(const TagConfiguration &configuration);
	private: 
		SharedTagConfiguration configuration;
	};




	class ConfigurableTagManagerFactory : public TagManagerFactory {
		explicit ConfigurableTagManagerFactory(const TagConfiguration &configuration = TagConfiguration());
		virtual ~ConfigurableTagManagerFactory();
		virtual SharedTagManager create(const fs::path &path) const override;

		const TagConfiguration& getConfiguration() const;
		TagConfiguration& getConfiguration();
		void setConfiguration(const TagConfiguration &configuration);
	private:
		TagConfiguration configuration;
	};
}

