"""distutils

The main package for the Python Module Distribution Utilities.  Normally
used from a setup script as

   from distutils.core import setup

   setup (...)
"""

# This module should be kept compatible with Python 2.1.

__revision__ = "$Id: __init__.py 51309 2006-08-16 08:13:26Z marc-andre.lemburg $"

# Distutils version
#
# Please coordinate with Marc-Andre Lemburg <mal@egenix.com> when adding
# new features to distutils that would warrant bumping the version number.
#
# In general, major and minor version should loosely follow the Python
# version number the distutils code was shipped with.
#
__version__ = "2.5.0"