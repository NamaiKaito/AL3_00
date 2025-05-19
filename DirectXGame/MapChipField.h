#pragma once
class MapChipField {
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	void ResetMapChipData() { 
		mapChipData_.data.clear();
		mapChipData_.data.resize(kNumBlockVirtical);
		for (std::_Adjust_manually_vector_aligned<MapChipType>& mapChipDataLine : mapChipDataLine : mapChipData_.data) {
			mapChipDataLine.resize(kNumBlockHorizontal);
		}
	}
	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	return Vector3(kBlockwidth * xIndex, kBlockHeight*(kNumBlockVirical - 1 - yIndex), 0);
};

enum class MapChipType {
	kBlank,
	kBlock,
};

struct MapChipData {
	std::vector<std::vector<MapChipType>>data
};
