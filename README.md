# ![Logo](chrome/app/theme/chromium/product_logo_64.png) obsidian

oobsidian is an open-source browser project that aims to build a safer, faster,
and more stable way for all users to experience the web.

The project's web site is https://www.chromium.org.

if you do not have any familiarity with chromium at all it is recommended to Learn how to [Get Around the Chromium Source Code Directory
Structure](https://www.chromium.org/developers/how-tos/getting-around-the-chrome-source-code), as obsidian uses the same structural DEPS and other prerequisites that chromium uses accept with changes related to what i implament but the base chromium parts will remain in tact, but there will be extra files and folders and also i may remove any un used files from the project so i will keep a documented change on that in the docs folder.

For historical reasons, there are some small top level directories. Now the
guidance is that new top level directories are for product (e.g. Chrome,
Android WebView, Ash). Even if these products have multiple executables, the
code should be in subdirectories of the product.

If you found a bug, please file it at https://damonicproducts.wixsite.com/smithcloud/support.
