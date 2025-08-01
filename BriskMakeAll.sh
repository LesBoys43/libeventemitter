meson setup _
meson compile -C _
meson install -C _
cd _ && ninja lbclean && cd ..
rm -rf _