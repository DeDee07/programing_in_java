#include <raylib.h>
#include <string>
#include <vector>
#include <cmath>

enum class ScreenState {
    WARNING,
    MENU,
    OPTIONS,
    REPLAYS,
    GAME_LOADING,
    GAME,
    DEATH
};

enum class Language {
    PT_PT,
    PT_BR,
    EN,
    ES,
    FR
};

struct Translations {
    const char* warning_title;
    const char* warning_msg;
    const char* menu_start;
    const char* menu_options;
    const char* menu_replays;
    const char* menu_exit;
    const char* loading_msg;
    const char* options_title;
    const char* options_language;
    const char* language_chosen;
    const char* replays_title;
    const char* replays_empty;
    const char* death_msg;
};

Translations GetTranslations(Language lang) {
    switch (lang) {
    case Language::PT_PT:
        return { "Aviso", "Este jogo é fictício e apenas para demonstração.",
                 "Iniciar", "Opções", "Replays", "Sair",
                 "Carregando...", "Opções", "Idioma", "Idioma escolhido:",
                 "Replays", "Nenhum replay disponível.", "Você morreu!" };
    case Language::PT_BR:
        return { "Aviso", "Este jogo é fictício e só para demo.",
                 "Iniciar", "Opções", "Replays", "Sair",
                 "Carregando...", "Opções", "Idioma", "Idioma escolhido:",
                 "Replays", "Nenhum replay disponível.", "Você morreu!" };
    case Language::EN:
        return { "Warning", "This game is fictional and for demonstration only.",
                 "Start", "Options", "Replays", "Exit",
                 "Loading...", "Options", "Language", "Language chosen:",
                 "Replays", "No replays available.", "You died!" };
    case Language::ES:
        return { "Aviso", "Este juego es ficticio y solo para demostración.",
                 "Iniciar", "Opciones", "Repeticiones", "Salir",
                 "Cargando...", "Opciones", "Idioma", "Idioma elegido:",
                 "Repeticiones", "No hay repeticiones disponibles.", "¡Has muerto!" };
    case Language::FR:
        return { "Attention", "Ce jeu est fictif et uniquement pour démonstration.",
                 "Démarrer", "Options", "Replays", "Quitter",
                 "Chargement...", "Options", "Langue", "Langue choisie:",
                 "Replays", "Aucune relecture disponible.", "Vous êtes mort!" };
    default:
        return GetTranslations(Language::EN);
    }
}

struct Button {
    Rectangle rect;
    std::string text;
    bool hovered = false;

    Button() = default;

    Button(float x, float y, float w, float h, const std::string& t)
        : rect{ x, y, w, h }, text(t) {
    }

    void Draw(Color bg, Color fg) {
        Vector2 mouse = GetMousePosition();
        hovered = CheckCollisionPointRec(mouse, rect);
        DrawRectangleRec(rect, hovered ? Fade(bg, 0.8f) : bg);
        int fontSize = static_cast<int>(rect.height * 0.6f);
        int textWidth = MeasureText(text.c_str(), fontSize);
        DrawText(text.c_str(),
            (int)(rect.x + (rect.width - textWidth) / 2),
            (int)(rect.y + (rect.height - fontSize) / 2),
            fontSize, fg);
    }

    bool IsClicked() {
        return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
};

void DrawCloseButton(float x, float y, float size, bool hovered) {
    Color color = hovered ? RED : DARKGRAY;
    DrawRectangle(x, y, size, size, color);
    DrawLine(x + 5, y + 5, x + size - 5, y + size - 5, RAYWHITE);
    DrawLine(x + 5, y + size - 5, x + size - 5, y + 5, RAYWHITE);
}

float Clamp(float value, float min, float max) {
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

struct Game {
    ScreenState screen = ScreenState::WARNING;
    Language currentLang = Language::EN;
    Translations t = GetTranslations(Language::EN);

    Button btnStart, btnOptions, btnReplays, btnExit;
    std::vector<Button> langButtons;

    bool showWarning = true;
    Rectangle closeBtnRect = { 0, 0, 30, 30 };
    bool closeHovered = false;

    int screenWidth = 960;
    int screenHeight = 640;

    Vector2 playerPos, enemyPos;
    float playerSpeed = 200.0f;
    float enemySpeed = 100.0f;
    float playerSize = 40;
    float enemySize = 40;
    bool enemyActive = true;

    float loadingTime = 2.0f;
    float loadingElapsed = 0.0f;

    void SetLanguage(Language lang) {
        currentLang = lang;
        t = GetTranslations(lang);
    }

    const char* GetLanguageLabel(Language lang) {
        switch (lang) {
        case Language::PT_PT: return "Português (PT)";
        case Language::PT_BR: return "Português (BR)";
        case Language::EN: return "English";
        case Language::ES: return "Español";
        case Language::FR: return "Français";
        default: return "Unknown";
        }
    }

    void Init() {
        SetLanguage(currentLang);
        float centerX = screenWidth / 2.0f - 125;
        float startY = screenHeight / 2.0f - 120;

        btnStart = Button(centerX, startY, 250, 60, t.menu_start);
        btnOptions = Button(centerX, startY + 70, 250, 60, t.menu_options);
        btnReplays = Button(centerX, startY + 140, 250, 60, t.menu_replays);
        btnExit = Button(centerX, startY + 210, 250, 60, t.menu_exit);

        langButtons.clear();
        float langBtnSize = 60;
        float langStartX = screenWidth / 2.0f - (langBtnSize * 2.5f);
        float langY = screenHeight / 2.0f;
        const char* langLabels[] = { "PT", "BR", "EN", "ES", "FR" };
        for (int i = 0; i < 5; i++) {
            langButtons.emplace_back(langStartX + i * (langBtnSize + 10), langY, langBtnSize, langBtnSize, langLabels[i]);
        }

        closeBtnRect.x = screenWidth - 40;
        closeBtnRect.y = 20;

        playerPos = { screenWidth / 4.0f, screenHeight / 2.0f };
        enemyPos = { (screenWidth * 3) / 4.0f, screenHeight / 2.0f };
        enemyActive = true;
        loadingElapsed = 0.0f;
    }

    void Update(float dt) {
        Vector2 mousePos = GetMousePosition();

        switch (screen) {
        case ScreenState::WARNING:
            closeHovered = CheckCollisionPointRec(mousePos, closeBtnRect);
            if (closeHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                showWarning = false;
                screen = ScreenState::MENU;
            }
            break;

        case ScreenState::MENU:
            if (btnStart.IsClicked()) {
                loadingElapsed = 0.0f;
                screen = ScreenState::GAME_LOADING;
            }
            if (btnOptions.IsClicked()) screen = ScreenState::OPTIONS;
            if (btnReplays.IsClicked()) screen = ScreenState::REPLAYS;
            if (btnExit.IsClicked()) CloseWindow();
            break;

        case ScreenState::GAME_LOADING:
            loadingElapsed += dt;
            if (loadingElapsed >= loadingTime) {
                screen = ScreenState::GAME;
                playerPos = { screenWidth / 4.0f, screenHeight / 2.0f };
                enemyPos = { (screenWidth * 3) / 4.0f, screenHeight / 2.0f };
                enemyActive = true;
            }
            break;

        case ScreenState::GAME: {
            Vector2 moveDir = { 0, 0 };
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) moveDir.y -= 1;
            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) moveDir.y += 1;
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) moveDir.x -= 1;
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) moveDir.x += 1;

            if (moveDir.x != 0 || moveDir.y != 0) {
                float len = sqrtf(moveDir.x * moveDir.x + moveDir.y * moveDir.y);
                moveDir.x /= len;
                moveDir.y /= len;
            }

            playerPos.x = Clamp(playerPos.x + moveDir.x * playerSpeed * dt, 0, screenWidth - playerSize);
            playerPos.y = Clamp(playerPos.y + moveDir.y * playerSpeed * dt, 0, screenHeight - playerSize);

            if (enemyActive) {
                Vector2 toPlayer = { playerPos.x - enemyPos.x, playerPos.y - enemyPos.y };
                float dist = sqrtf(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
                if (dist > 0) {
                    toPlayer.x /= dist;
                    toPlayer.y /= dist;
                    enemyPos.x += toPlayer.x * enemySpeed * dt;
                    enemyPos.y += toPlayer.y * enemySpeed * dt;
                }
            }

            Rectangle playerRect = { playerPos.x, playerPos.y, playerSize, playerSize };
            Rectangle enemyRect = { enemyPos.x, enemyPos.y, enemySize, enemySize };
            if (enemyActive && CheckCollisionRecs(playerRect, enemyRect)) {
                enemyActive = false;
                screen = ScreenState::DEATH;
            }

            // ESC no jogo não faz nada para sair do programa ou menu
            // Só sai do jogo pelo botão sair no menu principal
            break;
        }

        case ScreenState::OPTIONS:
        case ScreenState::REPLAYS:
        case ScreenState::DEATH:
            closeHovered = CheckCollisionPointRec(mousePos, closeBtnRect);
            if (closeHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                screen = ScreenState::MENU;
            }
            if (screen == ScreenState::OPTIONS) {
                for (size_t i = 0; i < langButtons.size(); i++) {
                    Button& b = langButtons[i];
                    b.hovered = CheckCollisionPointRec(mousePos, b.rect);
                    if (b.IsClicked()) SetLanguage((Language)i);
                }
                // ESC nas opções volta para o menu
                if (IsKeyPressed(KEY_ESCAPE)) {
                    screen = ScreenState::MENU;
                }
            }
            break;
        }
    }

    void DrawWarning() {
        ClearBackground(RAYWHITE);
        DrawText(t.warning_title, 20, 20, 30, DARKGRAY);
        DrawText(t.warning_msg, 20, 70, 20, DARKGRAY);
        DrawCloseButton(closeBtnRect.x, closeBtnRect.y, closeBtnRect.width, closeHovered);
    }

    void DrawMenu() {
        ClearBackground(RAYWHITE);
        btnStart.text = t.menu_start;
        btnOptions.text = t.menu_options;
        btnReplays.text = t.menu_replays;
        btnExit.text = t.menu_exit;

        btnStart.Draw(DARKBLUE, RAYWHITE);
        btnOptions.Draw(DARKBLUE, RAYWHITE);
        btnReplays.Draw(DARKBLUE, RAYWHITE);
        btnExit.Draw(DARKBLUE, RAYWHITE);
    }

    void DrawOptions() {
        ClearBackground(RAYWHITE);
        int titleFont = 40;
        int optionFont = 30;

        DrawText(t.options_title, screenWidth / 2 - MeasureText(t.options_title, titleFont) / 2, 50, titleFont, DARKBLUE);

        DrawText(t.options_language, screenWidth / 2 - 100, screenHeight / 2 - 60, optionFont, BLACK);

        for (auto& b : langButtons) {
            b.Draw(DARKBLUE, RAYWHITE);
        }

        std::string chosen = std::string(t.language_chosen) + " " + GetLanguageLabel(currentLang);
        DrawText(chosen.c_str(), screenWidth / 2 - MeasureText(chosen.c_str(), optionFont) / 2, screenHeight / 2 + 50, optionFont, DARKGRAY);

        DrawCloseButton(closeBtnRect.x, closeBtnRect.y, closeBtnRect.width, closeHovered);
    }

    void DrawReplays() {
        ClearBackground(RAYWHITE);
        DrawText(t.replays_title, screenWidth / 2 - MeasureText(t.replays_title, 40) / 2, 50, 40, DARKBLUE);
        DrawText(t.replays_empty, screenWidth / 2 - MeasureText(t.replays_empty, 20) / 2, screenHeight / 2, 20, DARKGRAY);
        DrawCloseButton(closeBtnRect.x, closeBtnRect.y, closeBtnRect.width, closeHovered);
    }

    void DrawLoading() {
        ClearBackground(RAYWHITE);
        DrawText(t.loading_msg, screenWidth / 2 - MeasureText(t.loading_msg, 40) / 2, screenHeight / 2 - 20, 40, DARKBLUE);

        int barWidth = 300;
        int barHeight = 25;
        float progress = loadingElapsed / loadingTime;
        if (progress > 1.0f) progress = 1.0f;

        int x = screenWidth / 2 - barWidth / 2;
        int y = screenHeight / 2 + 20;

        DrawRectangle(x, y, barWidth, barHeight, LIGHTGRAY);
        DrawRectangle(x, y, (int)(barWidth * progress), barHeight, DARKBLUE);
    }

    void DrawGame() {
        ClearBackground(BLACK); // fundo preto conforme pedido

        // Parâmetros do azulejo
        const int tileSize = 50; // Tamanho de cada azulejo
        const int rows = screenHeight / tileSize; // Número de linhas de azulejos
        const int cols = screenWidth / tileSize; // Número de colunas de azulejos

        // Desenha o chão em azulejos
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                Color tileColor = ((x + y) % 2 == 0) ? LIGHTGRAY : DARKBLUE; // Alterna as cores para simular azulejos
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, tileColor);
            }
        }

        // Desenha o player e o inimigo
        DrawRectangleV(playerPos, { playerSize, playerSize }, BLUE);
        if (enemyActive) DrawRectangleV(enemyPos, { enemySize, enemySize }, RED);
    }
    
    void DrawDeath() {
        ClearBackground(RAYWHITE);
        DrawText(t.death_msg, screenWidth / 2 - MeasureText(t.death_msg, 40) / 2, screenHeight / 2 - 20, 40, RED);
        DrawCloseButton(closeBtnRect.x, closeBtnRect.y, closeBtnRect.width, closeHovered);
    }
};

int main() {
    Game game;
    game.Init();

    InitWindow(game.screenWidth, game.screenHeight, "The Last Chace - Demo");

    SetExitKey(KEY_NULL); // Desativa a tecla ESC como saída da aplicação

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        game.Update(dt);

        BeginDrawing();
        switch (game.screen) {
        case ScreenState::WARNING:
            game.DrawWarning();
            break;
        case ScreenState::MENU:
            game.DrawMenu();
            break;
        case ScreenState::OPTIONS:
            game.DrawOptions();
            break;
        case ScreenState::REPLAYS:
            game.DrawReplays();
            break;
        case ScreenState::GAME_LOADING:
            game.DrawLoading();
            break;
        case ScreenState::GAME:
            game.DrawGame(); // Vai chamar a nova versão com azulejos
            break;
        case ScreenState::DEATH:
            game.DrawDeath();
            break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
