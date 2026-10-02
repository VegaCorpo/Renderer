#include "OBJLoader.hpp"
#include <format>
#include <fstream>
#include <sstream>
#include <unordered_map>

render::OBJLoader::Index render::OBJLoader::parseFaceToken(const std::string& token)
{
    Index idx;
    std::stringstream ss(token);
    std::string part;
    std::getline(ss, part, '/');
    idx.v = part.empty() ? 0 : std::stoi(part);
    if (std::getline(ss, part, '/')) {
        idx.vt = part.empty() ? 0 : std::stoi(part);
    }
    if (std::getline(ss, part, '/')) {
        idx.vn = part.empty() ? 0 : std::stoi(part);
    }
    return idx;
}

std::expected<void, std::string> render::OBJLoader::load(const std::string& filepath, ModelData& outModel)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return std::unexpected(std::format("[OBJLoader] cannot open file: {}", filepath));
    }

    std::vector<Eigen::Vector3f> positions;
    std::vector<Eigen::Vector3f> normals;
    std::vector<Eigen::Vector2f> uvs;
    std::unordered_map<std::string, unsigned int> cache;

    outModel.vertices.clear();
    outModel.indices.clear();

    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        std::stringstream ss(line);
        std::string tag;
        ss >> tag;

        if (tag == "v") {
            Eigen::Vector3f p;
            ss >> p.x() >> p.y() >> p.z();
            positions.push_back(p);
        } else if (tag == "vn") {
            Eigen::Vector3f n;
            ss >> n.x() >> n.y() >> n.z();
            normals.push_back(n);
        } else if (tag == "vt") {
            Eigen::Vector2f uv;
            ss >> uv.x() >> uv.y();
            uvs.push_back(uv);
        } else if (tag == "f") {
            std::vector<std::string> tokens;
            std::string token;
            while (ss >> token)
                tokens.push_back(token);

            for (std::size_t i = 1; i + 1 < tokens.size(); ++i) {
                for (const std::string& t : {tokens[0], tokens[i], tokens[i + 1]}) {
                    if (auto it = cache.find(t); it != cache.end()) {
                        outModel.indices.push_back(it->second);
                        continue;
                    }
                    Index idx = parseFaceToken(t);

                    if (idx.v > static_cast<int>(positions.size()) || idx.vn > static_cast<int>(normals.size()) ||
                        idx.vt > static_cast<int>(uvs.size())) {
                        return std::unexpected(
                            std::format("[OBJLoader] {}:{}: face references out-of-range index (v={}, vt={}, vn={})",
                                        filepath, lineNumber, idx.v, idx.vt, idx.vn));
                    }

                    Vertex vertex{};
                    vertex.position = idx.v > 0 ? positions[idx.v - 1] : Eigen::Vector3f::Zero();
                    vertex.normal = idx.vn > 0 ? normals[idx.vn - 1] : Eigen::Vector3f::UnitY();
                    vertex.uv = idx.vt > 0 ? uvs[idx.vt - 1] : Eigen::Vector2f::Zero();

                    auto newIndex = static_cast<unsigned int>(outModel.vertices.size());
                    outModel.vertices.push_back(vertex);
                    cache[t] = newIndex;
                    outModel.indices.push_back(newIndex);
                }
            }
        }
    }

    if (outModel.vertices.empty()) {
        return std::unexpected(std::format("[OBJLoader] {}: file parsed but produced no vertices", filepath));
    }
    return {};
}
