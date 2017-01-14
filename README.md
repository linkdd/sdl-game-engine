# SDL Game Engine

This project aims to create a full 2D game engine for the SDL2 library.

## Features

### Asset management

The ``AssetManager`` has a set of **Locators** and **Loaders**.

A **locator** is used to check if the requested asset exists. It will return a pointer
to the asset location.

Example:

 - ``FileLocator``: check if the requested asset exists on-disk.
 - ``ZipLocator``: check if the requested asset exists in a ZIP archive (*todo*).
 - ``URLLocator``: check if the requested asset exists at a URL (*todo*).

A **loader** is used to load the asset from the pointer returned by the **locator**.

Example:

 - ``ImageLoader``: using **SDL2_image**, loads an image.
 - ``FontLoader``: using **SDL2_ttf**, loads a TTF font.
 - ``JSONLoader``: loads a JSON file.
 - ``AudioLoader``: loads a sound file (*todo*).

Asset requests are made using an ``AssetDescriptor``. The descriptor holds all
informations about the asset (ie: name, font size, bit rate, ...).

The **manager** holds a cache of asset and descriptors. If a descriptor has already
been loaded, the same asset is returned.

### Actions management

Map keys, mouse buttons and controller buttons to a named action, and then check
in your code if the action is triggered or not.

### Scene management

The ``SceneManager`` keeps track of all your game's scenes. It handles the scene
loading and unloading, and notify the scene's graph of inputs, updates, and draw
requests.

The **scene graph** is a tree of node, each one implementing a specific task:

 - when a node enters the tree, it will be notified.
 - when all node's children have entered the tree, the node will be notified.
 - when a node leaves the tree, it will be notified.
 - when the scene receives an input, all nodes of the graph handling inputs will receive it.
 - when the scene must be updated, all nodes of the graph handling updates will be notified.
 - when the scene must be drawn, all nodes of the graph handling drawing will be notified.

Example of nodes:

 - ``PositionNode``: handle relative and absolute position
 - ``SpriteNode``: loads an asset and draw at a position
 - ``AnimatedSpriteNode``: loads multiple asset, change the frame on update, draw at a position
 - ``AreaNode``: notified when overlaps with another ``AreaNode``
 - ...

In order to create a ``Scene``, you just need to inherit from it, and creates your
nodes in the ``load()`` method, and delete them in the ``unload()`` method.

### Initializers

If you want to initialize libraries (ie: Stemworks API) and unload them at shutdown,
just inherit from ``Initializer`` and add it to the engine instance.

At the moment, the following initializers are enabled by default:

 - SDL2
 - SDL2_image
 - SDL2_ttf
 - SDL Window/Renderer creation

### Configuration

The engine instance is initialized with a configuration object, used to customize
how the engine will works. Feel free to use it to customize:

 - actions (for configurable controls in your game)
 - some of your nodes
 - ...

**NB:** The configuration object does not handle loading from a file and saves.

## Build

You need ``cmake`` and a compiler supporting the **C++14** standard.

    $ mkdir __build__
    $ cd __build__
    $ cmake ..
    $ make

## License

This project is released under the MIT License.
