#pragma once
#ifndef BUILDCONFIG_BUILDCONFIG_H_
#define BUILDCONFIG_BUILDCONFIG_H_

#include <string>
#include <format>

/**
 * \brief The Config class holds all the build-time information passed from the build system.
 */
class Config
{
public:
    Config();
    std::string LAUNCHER_NAME;
    std::string LAUNCHER_DISPLAYNAME;
    std::string LAUNCHER_COPYRIGHT;
    std::string LAUNCHER_DOMAIN;
    std::string LAUNCHER_CONFIGFILE;
    std::string LAUNCHER_GIT;

    /// The major version number.
    int VERSION_MAJOR;
    /// The minor version number.
    int VERSION_MINOR;
    /// The hotfix number.
    int VERSION_HOTFIX;
    /// The build number.
    int VERSION_BUILD;

    bool IS_DEBUG_BUILD = false;

    /**
     * The version channel
     * This is used by the updater to determine what channel the current version came from.
     */
    std::string VERSION_CHANNEL;

    bool UPDATER_ENABLED = false;

    /// A short string identifying this build's platform. For example, "lin64" or "win32".
    std::string BUILD_PLATFORM;

    /// URL for the updater's channel
    std::string UPDATER_BASE;


    /// User-Agent to use.
    std::string USER_AGENT;

    /// User-Agent to use for uncached requests.
    std::string USER_AGENT_UNCACHED;


    /// URL for notifications
    std::string NOTIFICATION_URL;

    /// Used for matching notifications
    std::string FULL_VERSION_STR;

    /// The git commit hash of this build
    std::string GIT_COMMIT;

    /// The git refspec of this build
    std::string GIT_REFSPEC;

    /// This is printed on start to standard output
    std::string VERSION_STR;

    /**
     * This is used to open the news page with the "More news" button.
     * It defaults in CMakeLists.txt to "https://multimc.org/posts.html"
     */
    std::string NEWS_URL;

    /**
     * This is used to fetch the news RSS feed.
     * It defaults in CMakeLists.txt to "https://multimc.org/rss.xml"
     */
    std::string NEWS_RSS_URL;

    /**
     * API key you can get from paste.ee when you register an account
     */
    std::string PASTE_EE_KEY;

    /**
     * API key from registering an application in Microsoft Azure
     * See: https://portal.azure.com/#view/Microsoft_AAD_RegisteredApps/ApplicationsListBlade
     */
    std::string MSA_CLIENT_ID;

    /**
     * Client ID you can get from Imgur when you register an application
     */
    std::string IMGUR_CLIENT_ID;

    /**
     * Metadata repository URL prefix
     */
    std::string META_URL;

    std::string BUG_TRACKER_URL;
    std::string DISCORD_URL;
    std::string SUBREDDIT_URL;
    std::string PATREON_URL;

    std::string RESOURCE_BASE = "https://resources.download.minecraft.net/";
    std::string LIBRARY_BASE = "https://libraries.minecraft.net/";
    std::string API_BASE = "https://api.minecraftservices.com";
    std::string SESSION_BASE = "https://sessionserver.mojang.com";
    std::string TEXTURE_BASE = "http://textures.minecraft.net";
    std::string IMGUR_BASE_URL = "https://api.imgur.com/3/";
    std::string FMLLIBS_BASE_URL = "https://files.multimc.org/fmllibs/";
    std::string TRANSLATIONS_BASE_URL = "https://files.multimc.org/translations/";

    std::string LEGACY_FTB_CDN_BASE_URL = "https://dist.creeper.host/FTB2/";

    std::string ATL_DOWNLOAD_SERVER_URL = "https://download.nodecdn.net/containers/atl/";

    std::string TECHNIC_API_BASE_URL = "https://api.technicpack.net/";
    /**
     * The build that is reported to the Technic API.
     */
    std::string TECHNIC_API_BUILD = "multimc";

    /**
     * \brief Converts the Version to a string.
     * \return The version number in string format (major.minor.revision.build).
     */
    std::string printableVersionString() const;
};

extern const Config BuildConfig;

#endif // !BUILDCONFIG_BUILDCONFIG_H_