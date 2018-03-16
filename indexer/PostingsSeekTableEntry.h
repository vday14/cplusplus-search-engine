#pragma once

class PostingsSeekTableEntry {
public:
    PostingsSeekTableEntry() {
        offset = 0;
        realLocation = 0;
    }

    size_t offset;
    size_t realLocation;
};