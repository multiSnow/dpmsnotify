dpmsnotify
==========
 Print ``<power_level> <monitor status>`` each time the dpms level changed.
 Gracefully exit by SIGINT or SIGTERM.

Required:
---------
 - xcb
 - xcb-dpms

Build:
------
 .. code:: sh

  ./autogen.sh
  ./configure
  make

Run:
----
 .. code:: sh

  ./dpmsnotify

Note:
-----
 The 'wait for' function is using 'polling' now, but should use event, which is not implemented yet.
 (see https://gitlab.freedesktop.org/xorg/proto/xcbproto/-/merge_requests/2).
