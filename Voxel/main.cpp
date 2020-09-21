#include <math.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

typedef glm::vec2 float2;
typedef glm::vec3 float3;

void fetchVoxels(const float2& p, const float2& dir, float2& org, float2& hitted) {
    //���ߵ���ı߽�
    float2 corner = sign(dir);
    corner.x = glm::max(0.0f, corner.x);
    corner.y = glm::max(0.0f, corner.y);
    //���ߵ���߽�ľ���
    float2 absDir = abs(dir);
    absDir.x = glm::max(absDir.x, 0.00001f); //�����ĸΪ0
    absDir.y = glm::max(absDir.y, 0.00001f);
    float2 dlt = abs(corner - p);
    dlt = dlt / absDir;
    //ѡȡ��С���룬��������
    float2 mask(0.0);
    if (dlt.x > dlt.y) {
        mask.x = 1.0;
    }
    else {
        mask.y = 1.0;
    }
    //��û��еıߵ����
    org = mask * corner;
    //���㽻��
    float t = glm::min(dlt.x, dlt.y);
    hitted = p + dir * t;
}

int main() {
    {
        float2 p(0.5, 0.5);
        float2 dir = normalize(float2(-0.1, 0.7));
        float2 org, hitted;
        fetchVoxels(p, dir, org, hitted);
    }
    {

    }

    return 0;
}