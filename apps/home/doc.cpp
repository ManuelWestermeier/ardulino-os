/*
 * HomeApp Module
 *
 * This module defines the functionality of the "Home" app in the system,
 * allowing users to view and manage a list of applications (apps) and
 * external links, known as HomeLinks, which appear on the home screen.
 *
 * Main components:
 *
 * - `HomeLink` struct: Represents an individual link or app on the home screen,
 *   storing details like name, app ID, a flag indicating whether it’s an app
 *   (`isApp`), and any optional start arguments.
 *
 * - `homeLinks` vector: Stores all HomeLink instances, including:
 *   1. **Default Apps**: Predefined apps that are always available, such as
 *      "Wifi", "Browser", and "Clock". These default apps are initialized
 *      within the `Init` function and are marked with `isApp = true`.
 *   2. **User-Defined Links**: Additional links, which can be created by users
 *      and are stored in `/app-links.data`. These links are loaded on startup
 *      if they are unique and marked with `isApp = false`.
 *
 * - `appSelect` object: Provides selection and scrolling functionality for
 *   navigating the `homeLinks`.
 *
 * - Core Functions:
 *   - `AddHomeLink`: Adds a new HomeLink if its name is unique, saving it to
 *     both memory and a file (`/app-links.data`). The link's name, app ID,
 *     and any start argument are stored in `base64` encoded format to ensure
 *     safe and consistent file storage.
 *   - `RemoveHomeLink`: Removes a specified HomeLink, updating the list in
 *     memory and rewriting the file without the deleted link.
 *   - `Init`: Initializes the default apps and loads additional user-defined
 *     links from the `/app-links.data` file, decoding `base64` values to retrieve
 *     the original names, app IDs, and arguments. This ensures all links are
 *     unique in `homeLinks`.
 *   - `Update`, `Scroll`, `SwitchApp`: Handle updating the display, scrolling
 *     through the links, and switching to a selected app when clicked.
 *
 * - File Persistence and `base64` Encoding: Uses `LittleFS` to store
 *   additional HomeLinks persistently, encoding each link's properties
 *   (name, app ID, and start arguments) in `base64` format within `/app-links.data`.
 *   This ensures data integrity and compatibility across different devices.
 *
 * Organization of `homeLinks`:
 *   - The `homeLinks` vector maintains a structured order by first adding
 *     predefined default apps during initialization, followed by user-defined
 *     links from the filesystem.
 *   - Each link is checked for uniqueness using `IsHomeLinkUnique` to avoid
 *     duplicate entries, and entries are loaded from `/app-links.data` only
 *     if not already present.
 */
// author chatgpt (i havent rode it)