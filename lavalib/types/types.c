#include "types.h"

char *type_str(int typ) {

	switch (typ) {
		case TYPE_BP:
			return "(";

		case TYPE_EP:
			return ")";

		case TYPE_ID:
			return "id";

		case TYPE_N:
			return "n";

		case TYPE_C:
			return "c";

		case TYPE_STR:
			return "str";

		default:
			return "unk";
	}
}
