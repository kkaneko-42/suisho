#version 450

layout(row_major, set = 0, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(row_major, set = 2, binding = 0) uniform DynamicUniformBufferObject {
    mat4 model;
} dynamic;

layout(location = 0) out vec2 fragTexCoord;

// Counter clock wise strip rectangle
const vec2[4] vertices = vec2[](
    vec2(0.5, -0.5), vec2(-0.5, -0.5),
    vec2(0.5, 0.5), vec2(-0.5, 0.5)
);

const vec2[4] uvs = vec2[](
    vec2(1.0, 0.0), vec2(0.0, 0.0),
    vec2(1.0, 1.0), vec2(0.0, 1.0)
);

void main() {
    gl_Position = ubo.proj * ubo.view * dynamic.model * vec4(vertices[gl_VertexIndex], 0.0, 1.0);
    fragTexCoord = uvs[gl_VertexIndex];
}
