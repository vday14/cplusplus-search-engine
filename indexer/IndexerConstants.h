#pragma once

namespace IndexerConstants {
	 const string pathToIndex = "/build8000/";
	//const string pathToIndex = "/constraintSolver/index-test-files/twitter/";

	const size_t maxWordSize = 28;

    const size_t masterKeySize = 30;
    const size_t masterValueSize = 168;

    const size_t chunkSeekKeySize = 30;
    const size_t chunkSeekValueSize = 8;

    const size_t chunkWordSeekKeySize = 30;
    const size_t chunkWordSeekValueSize = 168;

    const size_t chunkSizeLimit = 1000000;

    const size_t saveEveryXEntries = 25;
}
