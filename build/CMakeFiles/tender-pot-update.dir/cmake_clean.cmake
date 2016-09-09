FILE(REMOVE_RECURSE
  "CMakeFiles/tender-pot-update"
  "po/tender_pi.pot.dummy"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/tender-pot-update.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
