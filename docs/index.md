---
layout: default
---
<div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.8";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>

<script>window.twttr = (function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0],
    t = window.twttr || {};
  if (d.getElementById(id)) return t;
  js = d.createElement(s);
  js.id = id;
  js.src = "https://platform.twitter.com/widgets.js";
  fjs.parentNode.insertBefore(js, fjs);

  t._e = [];
  t.ready = function(f) {
    t._e.push(f);
  };

  return t;
}(document, "script", "twitter-wjs"));</script>

<div class="fb-like" data-href="https://linkdd.github.io/sdl-game-engine/" data-layout="button_count" data-action="like" data-size="large" data-show-faces="true" data-share="true"></div>

<a class="twitter-share-button"
  href="https://twitter.com/intent/tweet?text=SDLGameEngine%20A%202D%20game%20engine%20easy%20to%20use"
  data-size="large">
    Tweet
</a>

<!-- Place this tag where you want the +1 button to render. -->
<div class="g-plusone" data-size="tall" data-href="https://linkdd.github.io/sdl-game-engine"></div>

<!-- Place this tag after the last +1 button tag. -->
<script type="text/javascript">
  (function() {
    var po = document.createElement('script'); po.type = 'text/javascript'; po.async = true;
    po.src = 'https://apis.google.com/js/platform.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(po, s);
  })();
</script>

<a href="https://www.patreon.com/bePatron?u=4372210" data-patreon-widget-type="become-patron-button">
    Become a Patron!
</a>
<script async src="https://cdn6.patreon.com/becomePatronButton.bundle.js"></script>

------------

# Features

## Asset management

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

## Actions management

Map keys, mouse buttons and controller buttons to a named action, and then check
in your code if the action is triggered or not.

## Scene management

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

## Initializers

If you want to initialize libraries (ie: Stemworks API) and unload them at shutdown,
just inherit from ``Initializer`` and add it to the engine instance.

At the moment, the following initializers are enabled by default:

 - SDL2
 - SDL2_image
 - SDL2_ttf
 - SDL Window/Renderer creation

## Configuration

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

# License

This project is released under the MIT License.
