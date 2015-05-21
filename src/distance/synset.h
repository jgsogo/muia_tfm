
#pragma once

#include <iostream>
#include "wnb/core/wordnet.hh"

namespace wnb {
	// We will use synsets as concepts
	//typedef wnb::synset synset;

	//! Print synset
	inline std::ostream& operator <<(std::ostream& os, const synset& s) {
		os << s.words[0] << " [" << wnb::get_name_from_pos(s.pos) << "] ";
		for (auto& w : s.words) {
			os << w << ", ";
		}
		return os;
	}
}